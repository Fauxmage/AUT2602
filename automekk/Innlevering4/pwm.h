#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/cpufunc.h>
#include <adc.h>

/* Period, position, mode(?) */
void init_pwm(uint16_t per, uint16_t p);
/* Set period p for servo */
void pwm_set_p(uint16_t p);

/* Init LED, mode swap */
void init_leddies();
/* Input selector for MUX */
void pmux_out(uint8_t sel);

void dim_leds(uint16_t per, uint16_t p);
void led_set_p(uint16_t p);

/* Selector for [P4, P5, P6] */
void init_pwm_selector(uint16_t p, uint8_t selector);
/* Init for supporting servos on [P4, P5, P6] */
void init_pwm_tri(uint16_t per, uint16_t p, uint8_t selector);

void button_angles(uint8_t output);
uint16_t map_angle(uint8_t angle);
void servo_ctrl(uint8_t output, uint8_t angle);

uint8_t adc_to_angle(uint16_t adc_val);

#endif /* PWM_H_ */
