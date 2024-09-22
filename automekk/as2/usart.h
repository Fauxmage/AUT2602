
#ifndef USART_H
#define USART_H

#include <avr/io.h>


void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx);
void usart_send_char(USART_t *u_num, char i);

#endif /* USART_H */
