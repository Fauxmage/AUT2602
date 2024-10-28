/*
 * Ulrik Brochmann, ubr004@uit.no
 */

#define F_CPU 4000000UL //16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"
#include "timer.h"
#include "pwm.h"

#define BUFF 16

/* Period and position  */
#define PERIOD 10000 
#define P_NEUT 750	// 1.5 ms pulse
#define P_MIN 500	// 1.0 ms pulse
#define P_MAX 1000  // 2.0 ms pulse

/* Output selectors for PORTMUX */

#define PWM_0 0	// Transistors Q4-Q6
#define PWM_1 1 
#define PWM_2 2

#define LEDS 3	// LED0-2

/* Internal and external clock */
#define INT_CLK 0
#define EXT_CLK 1


int main(void) {
	// Initialize USART3, PB, Baudrate 9600, tx-pin as outputusart_usb_init
	usart_usb_init(9600);
	init_temp_sensor();
		
	uint8_t selector = LEDS;
	pmux_out(selector);
	

	uint16_t p_pwm = P_NEUT;
	//init_pwm(PERIOD, p_pwm);
	init_pwm_tri(PERIOD, p_pwm, PWM_0);

	uint16_t p_led = P_MIN;
	init_leddies(PERIOD, p_led);

	sei();
	while (1) {
		/* Pos of servo 0 to 180 degrees */
        for(p_pwm = P_MIN; p_pwm <= P_MAX; p_pwm += 10){
            init_leddies(PERIOD, p_pwm);
            _delay_ms(20);
        }
		/* Pos of servp 180 bsck to 0 degrees */
        for(p_pwm = P_MAX; p_led >= P_MIN; p_led -= 10){
            init_leddies(PERIOD, p_pwm);
			_delay_ms(20);
        }
        
		/* Iterate pulse val from MIN -> MAX, then MAX -> MIN */
        for(p_led = P_MIN; p_led <= P_MAX; p_led += 10){
            init_leddies(PERIOD, p_led);
            _delay_ms(5);
        }
        for(p_led = P_MAX; p_led >= P_MIN; p_led -= 10){
            init_leddies(PERIOD, p_led);
			_delay_ms(5);
        }
		
		_delay_ms(1000);
	}
}
