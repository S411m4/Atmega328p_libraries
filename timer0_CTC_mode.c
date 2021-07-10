//in CTC mode : WGM00 and WGM02 are cleared, while WGM01 is set to 1

//what happens in this mode
//1. we put  value to compare with in OCR0x (compare register) to be compared with value in TCNT0
//2. when value in TCNT0 = value in OCR0x, counter register TCNT0 is cleared where (OCR0x = TOP value)
//3. when compare match happens OCF0x flag is set
//4. and MCU goes to ISR (if its mask OCIE0x and general interrupt flag sei() are enabled)
//5.then OCF0x is cleared

//this mode is used to control wave frequency or produce sinewaves by altering values in OCR0x using registers COM0x in toggle state

//we can calculate produced wave frequency from the follwoing equation
//f_OC0x = f_clck / (2N * (1 + TOP))
// where TOP = value of OCR0x , N is the prescalar (1, 8, 64, 1024, 256)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000
int main(void)
{
	DDRD=0xFF; // set PD as output port
	TCCR0A |= (1 << WGM01); // set timer mode to CTC
	TCCR0A |= (1<<COM0A0); // toggle OC0A at each match, if it is 1 set to 0 and vice versa on each compare match
	OCR0A= 24; // set the max value in OCR0A, by changing this value we can control wave frequency (if we use toggle command above)
	TIMSK0 |= (1 << OCIE0A); // enable OCIE0A interrupt mask
	sei(); //general interrupt mask
	TCCR0B |= (1 << CS02) | (1<<CS00); // set prescalar to 1024
	while (1)
	{

  }
}

//we didn't write an interrupt service routine ISR, because we don't anything to happen on Compare match interrupt except toggle action

//if we want to change the frequency of wave by time we can add the following ISR
/*
ISR(TIMER0_COMPA_vect) //ISR for timer0 compare A
{
  OCR0A OCR0A + 3;  //add 3 to the TOP value each time (by increasing TOP value, frequency decrease)
}
*/

//dont forget to set a condition in the main function to restart the  OCR0x value to its inital value at certain point to prevent overflow
/*
while(1)
{
  if(OCR0A == 0x1F) //certain value to reset 
  {
    OCR0A = 0x01; //intial value 
   }
}
