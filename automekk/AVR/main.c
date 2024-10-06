/*
 * Ulrik Brochmann, ubr004@uit.no
 */


#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"
#include "timer.h"

#define BUFF 16

#define INT_CLK 0
#define EXT_CLK 1


int main(void) {
	// Initialize USART3, PB, Baudrate 9600, tx-pin as outputusart_usb_init
	usart_usb_init(9600);
	init_temp_sensor();
	
	
	t_clock_init(65535, TCA_SINGLE_CLKSEL_DIV256_gc);
	

	scale_frequency(1000, 5000, 256);
	scale_buzz(16000, 350, 256);
	sei();
	while (1) {
		uint8_t temp = adc_read_temp();
		// printf("Temp: %dC\n", temp);

		_delay_ms(1000);
  }
}
