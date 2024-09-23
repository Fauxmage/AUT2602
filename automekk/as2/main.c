/*
* Ulrik Brochmann, ubr004@uit.no
*/
#include "adc.h"
#include "usart.h"
#include "config.h"

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>


#define BUFFER 32
#define MS_DELAY 1000
#define B_RATE 9600
#define TX_PIN 0


int main(void){
    // Initialize USART3, PB, Baudrate 9600, tx-pin as output
    usart_init(&USART3, &PORTB, B_RATE, TX_PIN);
    
	init_temp_sensor();	
	
    char buffer[BUFFER];

    while(1){
        printf(buffer, "Temp: %d C\n", adc_read_temp());
        usart_transmit_data(&USART3, buffer);
        _delay_ms(1000);
    }
}
