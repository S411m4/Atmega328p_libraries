#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#define motor1_clockwise PD2
#define motor1_anticlockwise PD3
#define motor2_clockwise PD4
#define motor2_anticlockwise PD7
#define motor1_enable PD6  //if pwm is used to conrol speed on motor1
#define motor2_enable PD5 //if pwm is used to control speed on motor2

void motor_init(void)
{
	DDRD |= (1 << motor1_clockwise) | (1 << motor1_anticlockwise) | (1 << motor2_clockwise) | (1 << motor2_anticlockwise) | (1 << motor1_enable) | (1 << motor2_enable); //intialize H-bridge pins as OUTPUT
}

void forward(void)
{
	PORTD |= (1 << motor1_clockwise) | (1 << motor2_clockwise);
	PORTD &=~ ((1 << motor1_anticlockwise) | (1 << motor2_anticlockwise)); //make sure other directions are disables
}

void backward(void)
{
	PORTD |= (1 << motor1_anticlockwise) | (1 << motor2_anticlockwise);
	PORTD &=~ ((1 << motor1_clockwise) | (1 << motor1_clockwise));
	
}

void turn_right(void)
{
	PORTD |= (1 << motor1_clockwise) | (1 << motor2_anticlockwise);
	PORTD &=~ ((1 << motor1_anticlockwise) | (1 << motor2_clockwise));
}

void turn_left(void)
{
	PORTD |= (1 << motor2_clockwise) | (1 << motor1_anticlockwise);
	PORTD &=~  ((1 << motor2_anticlockwise) | (1 << motor1_clockwise));

}

void stop(void)
{
	PORTD &=~ ((1 << motor1_enable) | (1 << motor2_enable));
}

void motors_speed(float speedA, float speedB)
{
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << WGM02); //set timer in fast PWM mode
	TCCR0A |= (1 << COM0A0) | (1 << COM0A1); //inverted PWM on OC0A
	TCCR0A |= (1 << COM0B0) | (1 << COM0B1); //inverted PWM on OC0B
	
	TCCR0B |= (1 << CS02) | (1 << CS00); //set prescalar to 1024
	
	//speedA, speedB are the duty cycle percents
	
	OCR0A = 128;
	OCR0B = 255;
	//OCR0A = round(255 - (speedA * 255)); //set TOP value in OCR0A, to control duty cycle
	//OCR0B = round(255 - (speedB * 255)); //set TOP value in OCR0B, to control duty cyle
}


