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

#define BUFF 16

int main(void) {

  // Initialize USART3, PB, Baudrate 9600, tx-pin as output
  usart_usb_init(9600);

  init_temp_sensor();

  while (1) {
    uint8_t temp = adc_read_temp();
    printf("Temp: %dC\n", temp);

    _delay_ms(1000);
  }
}
