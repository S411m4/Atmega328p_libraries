//fast pwm mode:
//fast pwm mode is twice as fast as phase correct pwm because in fast pwm there is only one inclination when gonig up, while in phase correct pwm there is two inclinations
//by setting WGM02, WGM01, WGM00 = 011
//TCNT0, increment from zero till max value ( = 255), then goes to zero and start incrementing again

//by setting WGM02, WGM01, WGM00 = 111
//TCNT0, increment from zero till TOP value (compare register value), then goes to zero and start incrementing again

//it can be in two statees:
//1. inverted pwm : OC0x is set HIGH when TCNT0 = OCR0x, and is cleared when TCNT0 = zero
//in this case , duty cycle decreases by increasing value in compare register

//2. non-inverted pwm: OC0x is cleared (LOW) when TCNT0 = OCR0x, and is set HIGH when TCNT0 = zero
//in this caae, duty cycle increases by increasing value in compare register

//at the end of every cycle, overflow happens and TOV0 flag is set (and in this case, if we activated TOIEO (overflow interrupt flag) and sei(), we can go to ISR and we can change value of OCR0A as we need)

//difference between CTC and pwm is:
//CTC: value in comapre register control wave frequency and periodic time
//pwm: value in compare register control duty cycle (on time) while frequency and periodic time ( = overflow time) are constant

//we can calculate frequency of wave generated from
f_OCOApwm = f_clck / (N*256)

//we can calculate duty cycle from
//duty cycle = (time_on) / (time_on + time_off)

//inverted pwm:
//duty_cycle (time_on) = (255 - OCR0x) / 255

//non-inverted pwm:
//off_time = total_time - duty_cycle = (255-OCR0x) / 255
//(do 100% - duty cycle to calculate the required duty cycle)
//so
//duty_cycle = 1 - ((255 - OCR0x) / 255)

//for example

//at OCR0A = 192, duty cycle = 25% (inverted) and 75% (non-inverted)
//at OCR0A = 128, duty cyle = 50% (inverted) and 50% (non-inverted)
//at OCR0A = 1, duty cycle = 100% (inverted) and 0% (non-inverted)
//at OCR0A = 0, duty cycle = 0% (inverted) and 100% (non-inverted)




#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000
int main(void)
{
	DDRD = 0xFF; //set PD as output port
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << WGM02); //set time in fast pwm mode (mode 7)
	TCCR0A |= (1 << COM0A0) | (1 << COM0A1); //inverted pwm on OC0A (by increasing value in OCR0x, duty cycle decrease)
	TCCR0A |= (1 << COM0B1) ; //non-inverted pwm on OC0B (by increasing value in OCR0x, duty cycle increase)
  //becareful, that setting OC0B is also done in TCCR0a register
	
	OCR0A = 50; //set TOP value in OCR0A
	OCR0B = 50; //set TOP value in OCR0B
	
	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescalar to 1024
	
	while(1)
	{
		
		
	}
}
