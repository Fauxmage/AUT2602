#include "usart.h"

void usart_init(USART_t *u_num, PORT_t *u_port, uint16_t baud, uint8_t tx)
	
	// Calculate baudrate
	u_num->BAUD = ((64*F_CPU / (16 * (float)BAUD)) + 0.5)
	u_num->CTRLB |= USART_TXEN_bm | USART_RXMODE_NORMAL_gx;
	// Set to output
	u_port->DIRSET |= (1 << tx);
	
}

void usart_transmit_data(USART_t *u_num const char *data_str)
{
	while(*data_str)
	{
		while(!(u_num->STATUS & USART_DREIF_bm));
		u_num->TXDATAL = *data_str++;
	}
}

