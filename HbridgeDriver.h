#ifndef HbridgeDriver_H_
#define HbridgeDriver_H_


#define motor1_clockwise PD1
#define motor1_anticlockwise PD2
#define motor2_clockwise PD3
#define motor2_anticlockwise PD7
#define motor1_enable PD6  //if pwm is used to conrol speed on motor1
#define motor2_enable PD5 //if pwm is used to control speed on motor2

void motor_init(void);
void forward(void);
void backward(void);
void turn_right(void);
void turn_left(void);
void stop(void);
void motors_speed(float speedA, float speedB);

#endif