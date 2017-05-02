#include <msp430.h>

#define false 0;
#define true 1;

#define LED0 BIT0
double voltage;
double voltage_at_full_light=1.9;
double volts[7];
unsigned int samples[7];
int play_sound=false;
void ConfigureAdc();
void delay(double time);

void main(void)
{

   WDTCTL = WDTPW + WDTHOLD; // Stop WDT
   BCSCTL1 = CALBC1_1MHZ; // Set range
   DCOCTL = CALDCO_1MHZ;
   BCSCTL2 &= ~(DIVS_3); // SMCLK = DCO = 1MHz


   CCTL0 = CCIE;                             // CCR0 interrupt enabled
   TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode 1Mhz/8 = 125000
   CCR0 =  10000;                            //12.5Hz

   P2DIR=BIT0;
   P1SEL |= BIT6+BIT5+BIT4+BIT3+BIT2+BIT1+BIT0;
   ConfigureAdc();

   __enable_interrupt(); // Enable interrupts.


   while(1)
      {
         ADC10CTL0 &= ~ENC;
         while (ADC10CTL1 & BUSY);
         ADC10SA = (unsigned int)samples;
         ADC10CTL0 |= ENC + ADC10SC; // Sampling and conversion start
  //       __bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled
         int i;
         for(i=6;i>=0;i--)
         {
             volts[6-i]=(double)samples[i]*3.3/1024.0;
         }
         voltage=volts[0];







/****************************************************************************************************************
PART 2: Find what the voltage reads when the photoresistor is exposed to the room lighting
*****************************************************************************************************************/
         voltage_at_full_light=1.5;


/****************************************************************************************************************
PART 1: Create code that will only run if the voltage detected is greater than the full light voltage
*****************************************************************************************************************/

//the variable 'voltage' stores the value of the voltage across the photoresistor
//the variable 'voltage_at_full_light' stores the value of the voltage across the photoresistor under typical lighting conditions

         if(voltage>voltage_at_full_light)
         {
             delay(0.00454545454);
             play_sound=true;
         }


/****************************************************************************************************************
PART 3: Add additional keys!
*****************************************************************************************************************/


         ///* To add piano key to PIN 1.1 erase this line and line 86
         else if(volts[1]>voltage_at_full_light)
         {
             delay(0.00404953389);
             play_sound=true;
         }
         //erase me if line 80 is erased*/


         /* To add piano key to PIN 1.2 erase this line and line 95
         else if(volts[2]>voltage_at_full_light)
         {
             delay(0.00382225008);
             play_sound=true
         }
         erase me if line 89 is erased */


         /* To add piano key to PIN 1.3 erase this line and line 104
         else if(volts[3]>voltage_at_full_light)
         {
             delay(0.00340524066);
             play_sound=true;
         }
         erase me if line 98 is erased */


         /* To add piano key to PIN 1.4 erase this line and line 113
         else if(volts[4]>voltage_at_full_light)
         {
             delay(0.00303372286);
             play_sound=true;
         }
         erase me if line 107 is erased */


         /* To add piano key to PIN 1.5 erase this line and line 122
         else if(volts[5]>voltage_at_full_light)
         {
             delay(0.00286345882);
             play_sound=true;
         }
         erase me if line 116 is erased */


         /* To add piano key to PIN 1.6 erase this line and line 85
         else if(volts[6]>voltage_at_full_light)
         {
             delay(0.00255105294);
             play_sound=true
         }
         erase me if line 125 is erased */


/****************************************************************************************************************
END
*****************************************************************************************************************/

          else
          {
              play_sound=false;
          }

      }

}




#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer_A (void)
{
    if(play_sound==1)
    {
        P2OUT ^= BIT0; // Toggle P2.0
    }
}


//unused ADC interrupt
#pragma vector=ADC10_VECTOR

__interrupt void ADC10_ISR (void)

{

//   __bic_SR_register_on_exit(CPUOFF); // Return to active mode

}



void ConfigureAdc(void)

{

   /* Configure ADC Channel */

   ADC10CTL1 = INCH_6 + ADC10DIV_0 + CONSEQ_3 + SHS_0;

   ADC10CTL0 = SREF_0 + ADC10SHT_2 + MSC + ADC10ON + ADC10IE;

   ADC10AE0 = BIT6+BIT5+ BIT4 + BIT3 + BIT2 + BIT1 + BIT0;

   ADC10DTC1 = 7;

}


void delay(double period)
{
    double frequency=1.0/period;
    int q=(int)(125000.0/frequency);

    CCR0=q;
}
