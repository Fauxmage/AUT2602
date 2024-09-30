/*
 * Ulrik Brochmann, ubr004@uit.no
 */
#define F_CPU 4000000UL

#include "adc.h"
#include "usart.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <xc.h>

int main(void) {

  // Initialize USART3, PB, Baudrate 9600, tx-pin as output
  usart_usb_init();
  usart_init(&USART3, &PORTB, 0, 0);

  init_temp_sensor();

  char buffer[32];
  printf("Hello\n");

  sei();
  while (1) {

    sprintf(buffer, "TEMPERATURE! %dC \n", adc_read_temp());
    printf("T: %d\n", adc_read_temp());
    _delay_ms(100);
  }
}
