#include "usart.h"
#include "config.h"
#include <xc.h>
#include <avr/io.h>


void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx_pin){
	// Calculate baudrate
	uint16_t baud_setting = 9600; //(uint16_t)(((64 * F_CPU) / (16 * baud)) + 0.5);
	u_num->BAUD = baud_setting;

	// Enable transmitter
	u_num->CTRLB |= USART_TXEN_bm | USART_RXMODE_NORMAL_gc;
	
	// Set TXpin as output
	u_port->DIRSET |= (1 << tx_pin);
	
}

void usart_send_char(USART_t *u_num, char data){
    while (!(u_num->STATUS & USART_DREIF_bm));
    u_num->TXDATAL = data;
}

void usart_transmit_data(USART_t *u_num, const char *data_str){
    while (*data_str){
        usart_send_char(u_num, *data_str++);
    }
}
