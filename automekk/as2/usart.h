
#ifndef USART_H
#define USART_H

#include <avr/io.h>


void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx_pin);
void usart_send_char(USART_t *u_num, char i);
void usart_transmit_data(USART_t *u_num, const char *data_str);

#endif /* USART_H */
