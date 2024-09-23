#ifndef USART_H
#define USART_H

#include <xc.h>
#include <avr/io.h>
#include <stdio.h>

static uint8_t USART3_send_char (char c, FILE *stream);
static FILE new_std_out = FDEV_SETUP_STREAM (USART3_send_char, NULL, _FDEV_SETUP_WRITE);


void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx_pin);
void usart_send_char(USART_t *u_num, uint8_t data);
void usart_transmit_data(USART_t *u_num, char *data_str);

#endif /* USART_H_ */
