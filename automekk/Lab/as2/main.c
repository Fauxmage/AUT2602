/*
* Ulrik Brochmann, ubr004@uit.no
*/
#define F_CPU 4000000UL

#include "usart.h"
#include "adc.h"

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFER 32
#define MS_DELAY 1000
#define BAUDRATE 9600
#define TX_PIN 0


int main(void){
    // Initialize USART3, PB, Baudrate 9600, tx-pin as output
	usart_init(&USART3, &PORTB, 9600, 0);
	init_temp_sensor();
	
	char buffer[32];


	printf("Hello\n");
	
	uint16_t temp;

	sei();
    while(1){

		temp = adc_read_temp();

		printf("temp = %d\n", temp);

		printf("T%dC\n", 4);
		
        _delay_ms(1000);
    }
}
