#ifndef USART_H_
#define USART_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define TX_PIN_bp 0
#define RX_PIN_bp 1

// Setup for stdout
void usart_usb_init(uint16_t baud);
void usart_usb_transmit(char c);
char usart_usb_receive();

// Transmitting an array of characters
void usart_usb_transmit_char_array(uint8_t addEndLine, char string[],
                                   uint8_t length);

// Updated function signature with int return type
static uint8_t usart_usb_transmit_printf(char c, FILE *stream);

static FILE new_std_out = FDEV_SETUP_STREAM((void *)usart_usb_transmit_printf,
                                            NULL, _FDEV_SETUP_WRITE);

// Generic USART functions
void usart_init(USART_t *usart_nr, PORT_t *usart_port, uint16_t baud,
                uint8_t tx_bp);

void usart_transmit_char(USART_t *usart_nr, char c);

typedef void (*usart_char_transmitter)(USART_t *usart_nr, char c);

void usart_transmit_string(USART_t *usart_nr, char *string,
                           usart_char_transmitter transmit_char);

#endif /* USART_H_ */
