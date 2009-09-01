/******************************************************************************
*
* DEFCON 17 BADGE
*
* Filename:		  DC17_Badge.c
* Author:		    Joe Grand (Kingpin)
* Revision:		  1.0
* Last Updated: April 27, 2009
*
* Description:	Main File for the DEFCON 17 Badge (Freescale MC56F8006)
* Notes:
*
* See DC17_Badge.h for more inf0z...		
*******************************************************************************/

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PWMRed.h"
#include "PWMGreen.h"
#include "PWMBlue.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "DC17_Badge.h"


/****************************************************************************
 ************************** Global variables ********************************
 ***************************************************************************/

// Badge 
badge_state_type badge_state = GAME; // begin in GAME (For Simon!) mode on power-up
badge_type_struct badge_type;
struct packed_flags flags;

// Microphone
unsigned int freqcount = 0;
word	micval = 0;
word  micval_offset;

// FFT
dfr16_tRFFTStruct RFFT;
dfr16_tRFFTStruct *pRFFT = &RFFT;
CFrac16 FFTInplaceBuf[MAX_RFFT_LEN/2];
unsigned long FFTVal[3];

// A/D
unsigned int AdcBuffer[ADC_MAX_BUFFER_SIZE];
unsigned int AdcWriteIndex = 0;
unsigned int AdcReadIndex = 0;

// LED
led_state_type LEDstate = RED;
unsigned int LEDptr = 0;

// RNG
//unsigned int randtime = 0;
//int randval; 

// Sleep
byte threshold_failure;
word threshold_count;

// Modes
unsigned int soscount = 0;
unsigned int dancetmr = 0; 

// SIMON
led_state_type sequence[MAX_SIMON_SEQUENCE];
unsigned char current_sequence_location;
unsigned int current_sequence_length;

// CHOW'S ONESHOT CODE
unsigned int myBins[3] = {0,0,0};
unsigned int myAvg = 0;
bool bucket_timeout = FALSE;
unsigned int myTimer= 0;
bool go_bucket = FALSE;
unsigned int last_color = 0;

/****************************************************************************
 ************************** Functions ***************************************
 ***************************************************************************/

void dc17_badge(void)
{ 
	dc17_init();
  
	// We stripped out i2c communication because we don't need that shit right now.
	// It would have been nice to use it in order to connect multiple badges to
	// display colors for the Simon game.
  
  // begin normal operation
	
	game_menu();
	
/*  badge_state = FFT; // enable FFT-related functions in the interrupts
  while(1)
  {  	
  	if (badge_type != HUMAN) if (flags.i2c_rx); // if i2c data packet received, enter badge-to-badge mode (slave)
  
    dc17_fft();
    dc17_process_fft();
    dc17_sleep();
  }
*/  //Let's try ignoring this part for now

}


/**************************************************************/

void dc17_fft(void) // do tha' FFT
{
	
	unsigned int n=0;
	
 	unsigned int  	i;
 	Result 	    	res;
 	
  	unsigned long   Temp1, Temp2;    

 	if (flags.PerformFFT == true)
  	{      
   	// perform the FFT (N = 8)
    res = dfr16RFFT (pRFFT, (Frac16 *)&AdcBuffer[AdcReadIndex], (dfr16_sInplaceCRFFT *)&FFTInplaceBuf[0]);

    for (i = 1; i <= ((MAX_RFFT_LEN/2) - 1); i++) // ignore bin 0
    {
      // calculate the power of the ith element (bin) of the FFT
      // M = sqrt(real^2 + imag^2)
    // P = M^2
 	// since the power of a frequency element of the FFT is the square of the magnitude, we can just skip
	// the square root while calculating the magnitude and we're left with the power. 
	// we ignore the phase component of the FFT.     	
      Temp1 = abs_s(FFTInplaceBuf[i].real);
      Temp1 = Temp1*Temp1;
        
      Temp2 = abs_s(FFTInplaceBuf[i].imag);
      FFTVal[i-1] = (Temp2*Temp2) + Temp1;
	}	
		
		/*Term1_SendStr("\n\r0: ");
		Term1_SendNum((long)FFTVal[0]);
		Term1_SendStr("\t1: ");
		Term1_SendNum((long)FFTVal[1]);
		Term1_SendStr("\t2: ");
		Term1_SendNum((long)FFTVal[2]);*/
		
	//	Term1_SendNum((long)FFTVal[0]);
	//	Term1_SendStr("\n\r");
	
	
	
		
    AdcReadIndex += MAX_RFFT_LEN;

    if (AdcReadIndex >= ADC_MAX_BUFFER_SIZE)
    {
     	AdcReadIndex = 0;
    }

    flags.PerformFFT = false;
  }
  
  
}


void dc17_process_fft(void) // do stuff based on the calculated FFT data
{
	unsigned char i;

	// if sound energy is greater than our sleep threshold...
	if ((FFTVal[0] > SLEEP_THRESH) || (FFTVal[1] > SLEEP_THRESH) || (FFTVal[2] > SLEEP_THRESH))
	{
		threshold_failure++; // increment counter
 		flags.sleep = 0;	 // stay awake
		TI1_Enable();	 // make sure TMR1 is only enabled when the device is completely awake (to avoid flickering LED while sleeping)
	}
	
	if (!flags.sleep) // if we're awake
	{
		// super secret frequency detection code
	
			freqcount = 0;
				
		// choose our operating mode	
		// if we are in a loud environment (like a disco!), enter dance mode
		if (((FFTVal[0] > DANCE_THRESH) && (FFTVal[1] > DANCE_THRESH) && (FFTVal[2] > DANCE_THRESH)) || dancetmr) // all bins must be above the threshold to enter the mode
		{
		  // hysteresis to stay in dance mode for some amount of time after we go below the threshold
		  if (dancetmr) 
		    dancetmr--;
		  else 							// dancetmr = 0, so we've just entered this mode
		  	dancetmr = DANCE_TMR;	// set our timer

			if ((FFTVal[0] > (DANCE_THRESH >> 2)) || (FFTVal[1] > (DANCE_THRESH >> 2)) || (FFTVal[2] > (DANCE_THRESH >> 2)))
		  	dancetmr = DANCE_TMR; // reset the timer if any one bin has met grester than 1/2 threshold	 
		  	    
			for (i = 0; i < 3; ++i)
			{
			  FFTVal[i] >>= 2; // scale FFT value down to something more reasonable (we lose resolution at lower volumes, but that's OK, we're at the disco!)
				if (FFTVal[i] > 0xB000) FFTVal[i] = 0xB000; // and limit the maximum brightness
			}	
		
			// set LED colors and brightness based on input frequency			
			PWMRed_SetRatio16(~(unsigned int)FFTVal[0]); 
			PWMGreen_SetRatio16(~(unsigned int)FFTVal[1]); 
			PWMBlue_SetRatio16(~(unsigned int)FFTVal[2]); 
		
		  // if we've been in this mode for some amount of time, put out a mayday call (per DT!)
	
		}
	
		
  }
}

void dc17_init(void) // badge start-up/initialization
{
  unsigned int 		options = FFT_SCALE_RESULTS_BY_N; // unconditionally scale down the results by n

	Cpu_DisableInt(); // disable global interrupts 	
	PWMRed_Enable();  // while we enable all the modules
	PWMGreen_Enable();
	PWMBlue_Enable();
	MICOUT_Enable();

	//Term1_SendStr("Badge Hack: Simon\n\n\r");

  // take a listen at the current ambient noise
	/*MICOUT_Measure(TRUE); // number of conversions specified in ADC bean, wait for conversion to complete
	MICOUT_GetValue16(&micval); // get a/d sample  
	srand((unsigned int)micval); // ...seed the PRNG with the value */
  		
	TI0_Enable();
	TI1_Enable();
	Cpu_EnableInt();  // re-enable global interrupts when we're done and ready for action
 		
	// initialize global flags
	flags.PerformFFT = FALSE;
	flags.ptr_update = 0;
	flags.sleep = 0;
	  
  threshold_failure = 0; // counters for auto-power-off
  threshold_count = 0;
	
  // initialize the FFT algorithm
  dfr16RFFTInit (pRFFT, 8, options); // MAX_RFFT_LEN

}



/**************************************************************
/* INTERRUPT SERVICE ROUTINES
/**************************************************************/

void dc17_pit_isr(void) // Programmable Interval Timer (PIT): every 8ms, set to operate during Stop Mode
{  	   	
  if (badge_state == FFT)
  {
			// update the randomizer...  
			/*randtime++;
			if (randtime >= RAND_TMR) 
			{
				randval = rand() % 3; 
				randtime = 0;
			}*/
			
			// if noise energy is below our threshold for some amount of time, then go to sleep
 			if (threshold_failure == 0)
 			{
 				threshold_count++;
 			}
 			else
 			{
 				threshold_count = 0;
 				threshold_failure = 0;
 			}
 		
 			if (threshold_count > SLEEP_TMR)
 				flags.sleep = 1; 
 	}
 	
  // LEDptr used for RGB pulsing and blending tables
}


void dc17_t0_isr(void) // TMR0: A/D sampling, 8kHz (every 0.125ms) (Fmax = highest frequency that can be analyzed = Fs / 2 = 4kHz)
{
  if (badge_state == FFT)
  {  
		// get a/d sample and add it to our circular buffer
		MICOUT_Measure(TRUE); // number of conversions specified in ADC bean, wait for conversion to complete
		MICOUT_GetValue16(&micval);  	   
	  AdcBuffer[AdcWriteIndex] = micval;
	  AdcWriteIndex++;
	  
	  if (AdcWriteIndex >= ADC_MAX_BUFFER_SIZE) 
	  	AdcWriteIndex = 0; // wrap around to beginning of buffer
	  		
 		// check to see if it's time to do an FFT (e.g., we have enough new A/D samples)
    if (AdcReadIndex > AdcWriteIndex)
  	{
  		flags.PerformFFT = true;
  	}
  	else if (AdcReadIndex <= (int)(AdcWriteIndex - MAX_RFFT_LEN))
  	{
    	flags.PerformFFT = true;
  	}
  }
}


void dc17_t1_isr(void) // TMR1: RGB multiplexing, every 1ms
{
		switch (LEDstate)
		{
				case RED:
					setRegBit(GPIO_A_PER, PE0);
  	  		clrRegBit(GPIO_A_PER, PE1);
  	  		clrRegBit(GPIO_A_PER, PE2);
  				LEDstate = GREEN;
					break;
				case GREEN:
					clrRegBit(GPIO_A_PER, PE0);
  	  		setRegBit(GPIO_A_PER, PE1);
  	  		clrRegBit(GPIO_A_PER, PE2);
  				LEDstate = BLUE;					
  				break;
				case BLUE:
					clrRegBit(GPIO_A_PER, PE0);
  	  		clrRegBit(GPIO_A_PER, PE1);
  	  		setRegBit(GPIO_A_PER, PE2);
  				LEDstate = RED;				
					break;
		}
}

/**************************************************************
*	Function: 	delay
*	Parameters: 16-bit delay value
*	Return:		none
*
*	Simple delay loops
* These are not very accurate because they could get interrupted
**************************************************************/
 
void delay_ms(unsigned int ms)  // delay the specified number of milliseconds
{
  unsigned int i;

  for (i = 0; i < ms; ++i)
  	Cpu_Delay100US(10);
}


/****************************** END OF FILE **********************************/

void game_menu(void)
{
	PWMRed_SetRatio16(ON);
	PWMGreen_SetRatio16(ON);
	PWMBlue_SetRatio16(ON);
	
	delay_ms(500);
	
	simon_loop();
	
}

void simon_loop(void)
{
	int i, j;
	unsigned int ans_in;
	
	simon_clear_seq();
	
	for (i = 1; i <= MAX_SIMON_SEQUENCE; i++)
    {
    	simon_add_seq();
    	
    	// Flash the sequence
    	for (i = 0; i <= current_sequence_length; i++) 
    	{
    		simon_flash(sequence[i]);
			delay_ms(500);
			simon_flash(BLACK);
    	}
   		
   		//Term1_SendStr("\n\rSeq Done\n");
    	
    	
    	// Get answers
    	
    	for (j = 0; j <= current_sequence_length; j++) 
    	{
    		simon_flash(WHITE);
    		delay_ms(500);
    		
    		ans_in = one_shot();
    		
    		if(sequence[j] != (led_state_type)ans_in)
    		{
    			//Term1_SendStr("\n\rYOU FUCKING SUCK AT SIMON");
    			game_over_lose();
    		}
    		
    		delay_ms(250);
    		simon_flash(BLACK);
    	}
    }
    
    game_over_win();
    
}

void game_over_lose(void) 
{
	int i;
	for (i = 1; i <= 10; i++)
	{
		simon_flash(RED);
		delay_ms(250);
		simon_flash(BLACK);
		delay_ms(250);
	}
	
	game_menu();
	
}

void game_over_win(void) 
{
	int i;
	for (i = 1; i <= 10; i++)
	{
		simon_flash(GREEN);
		delay_ms(250);
		simon_flash(BLACK);
		delay_ms(250);
	}
	
}

//char max_bin() {
//  char max = 0;
//  if (FFTVal[1] > FFTVal[max]) max = 1;
//  if (FFTVal[2] > FFTVal[max]) max = 2;
//
// return max;
//}

void simon_add_seq() {
  sequence[current_sequence_length++] = (led_state_type) (rand() % 3);
  current_sequence_length = current_sequence_length++;
}
void simon_clear_seq() {
  current_sequence_length = 0;
}

//led_state_type simon_next_seq() {
//  return sequence[];
//}

void simon_flash(led_state_type color) {
  switch (color) {
  case RED:
    PWMRed_SetRatio16(ON);
    PWMGreen_SetRatio16(OFF);
    PWMBlue_SetRatio16(OFF);
    break;
  case GREEN:
    PWMRed_SetRatio16(OFF);
    PWMGreen_SetRatio16(ON);
    PWMBlue_SetRatio16(OFF);
    break;
  case BLUE:
    PWMRed_SetRatio16(OFF);
    PWMGreen_SetRatio16(OFF);
    PWMBlue_SetRatio16(ON);
    break;
  case WHITE:
    PWMRed_SetRatio16(ON);
    PWMGreen_SetRatio16(ON);
    PWMBlue_SetRatio16(ON);
    break;
  case BLACK:
    PWMRed_SetRatio16(OFF);
    PWMGreen_SetRatio16(OFF);
    PWMBlue_SetRatio16(OFF);
    break;
  }
}


// CHOWS COMPARISON CODE
// WHY AM I TYPING IN ALL CAPS

unsigned int one_shot(void)
{

	//set_color(500000,0,0);
    go_bucket=TRUE;
	
    while (go_bucket)
    {
	    dc17_fft();
    	fft_bucketer();
    }
	
	return last_color;
	
}

//void set_color(unsigned int r, unsigned int g, unsigned int b)
//{
//	PWMRed_SetRatio16(~(unsigned int)r); 
//	PWMGreen_SetRatio16(~(unsigned int)g); 
//	PWMBlue_SetRatio16(~(unsigned int)b); 
//}
void fft_bucketer(void)
{
	//increment the timeout counter...
	myTimer++;
	
	//set timeout flag true after 500 cycles
	if(myTimer>500)
		bucket_timeout = TRUE;
	
	
	if ((FFTVal[0] > SLEEP_THRESH) || (FFTVal[1] > SLEEP_THRESH) || (FFTVal[2] > SLEEP_THRESH || bucket_timeout))
	{
	
		//so its loud enuff, lets do the test
		
		//after so many samples, take the lagest myBin
		//and call it "the one" and rank it on sureness via how big the bin is
		
		//global vars used, myAvg, myBins[]
		if(myAvg == 100 ||bucket_timeout)
		{
		//ten samples taken
		//	Term1_SendStr("dun bucketing show result...\n\r");
			switch(which_is_bigger((long)myBins[0],(long)myBins[1],(long)myBins[2]))
			{
				case 0:
				Term1_SendStr("bin0\n");
				last_color = 0;
				break;
				case 1:
				Term1_SendStr("bin1\n");
				last_color = 1;
				break;
				case 2:
				Term1_SendStr("bin2\n");
				last_color = 2;
			}
			//reset shiz
			myBins[0] = 0;
			myBins[1] = 0;
			myBins[2] = 0;
			
			myAvg = 0;
			
			go_bucket = FALSE;
			myTimer=0;
			bucket_timeout = FALSE;
			
		}
		else
		{
			//keep adding to the bins
			Term1_SendStr("adding" );
			switch(which_is_bigger((long)FFTVal[0],(long)FFTVal[1],(long)FFTVal[2]))
			{
				case 0:
				myBins[0]++;
				//set_color(500000, 1, 1);
				break;
				
				case 1:
				myBins[1]++;
				//set_color((unsigned int)1, (unsigned int)500000, (unsigned int)1);
				break;
				
				case 2:
				myBins[2]++;
				//set_color((unsigned int)1, (unsigned int)1, (unsigned int)900000); 
			}
			
			myAvg++;
		}
		
		
	}
	
	
}
unsigned int which_is_bigger(long x, long y, long z)
{
	unsigned int biggest = 0;
	
		if ( x < y )
		{
			biggest = 1;
			
			if (y < z)
				biggest = 2;
		}
		else if (x < z)
			biggest = 2;
		
	//return 0 1 2 for x y z respectivly
	return biggest;
	
}