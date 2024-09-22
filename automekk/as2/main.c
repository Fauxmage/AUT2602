/*
* Ulrik Brochmann, ubr004@uit.no
*/
#define F_CPU 4000000UL

#include "usart.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER 32


int main(void){
    // Initialize
    usart_init(&USART3, &PORTB, 9600, PIN0_bp);
    init_tmp_sensor();
    
    char buffer[BUFFER];
    int16_t temperature;

    while(1)
    {
        temperature = adc_read_temp();
        sprintf(buffer, "Temp: %d C\r\n", temperature);
        usart_transmit_data(&USART3, buffer);
        _delay_ms(1000);
    }
}
