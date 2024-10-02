#define F_CPU 4000000UL
#include "usart.h"
#include "config.h"


#include <xc.h>
#include <avr/io.h>


USART_t *usart = NULL;

void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx_pin){
	// Calculate baudrate
	u_num->BAUD = B_RATE(baud);
	// Enable transmitter
	u_num->CTRLB |= USART_TXEN_bm | USART_RXMODE_NORMAL_gc;
	// Set TXpin(0) as output
	u_port->DIRSET |= (1 << tx_pin);
	usart = u_num;
}

void usart_send_char(USART_t *u_num, char data){
    while (!(u_num->STATUS & USART_DREIF_bm));
    u_num->TXDATAL = data;
}


static uint8_t USART3_send_char(char c, FILE *stream){ 
	usart_send_char(&USART3, c);
	return 0;
}


void usart_transmit_data(USART_t *u_num, char *data_str){
	for(uint8_t i = 0; data_str[i] != '\0'; i++){
		usart_send_char(&USART3, data_str[i]);
	}
}
