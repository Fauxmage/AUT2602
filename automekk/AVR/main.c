/*
 * Ulrik Brochmann, ubr004@uit.no
 */

#define F_CPU 4000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "adc.h"
#include "usart.h"
#include "rtc.h"

#define BUFF 16

#define INT_CLK 0
#define EXT_CLK 1

#define RTC_ENABLE 1
#define RTC_DISABLE 0


int main(void) {
	// Initialize USART3, PB, Baudrate 9600, tx-pin as outputusart_usb_init
	usart_usb_init(9600);
	init_temp_sensor();
	
	//rtc_init(RTC_ENABLE, INT_CLK);

	printf("This is a test!\n");

	while (1) {
		uint8_t temp = adc_read_temp();
		printf("Temp: %dC\n", temp);

		_delay_ms(1000);
  }
}
