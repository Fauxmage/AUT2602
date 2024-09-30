#include "usart.h"
#include "config.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile char transmit_buffer[100];
volatile uint8_t next = 0;
volatile uint8_t last = 0;

char usb_message[256];
volatile uint8_t marker_pos;
volatile uint8_t usb_message_ready;

// Define the actual stream and function
FILE new_std_out =
    FDEV_SETUP_STREAM(usart_usb_transmit_printf, NULL, _FDEV_SETUP_WRITE);

void usart_usb_init() {
  /* Necessary configuration */
  USART3.BAUD = 9600; // Baudrate 9600 // F_CPU = 4M
  USART3.CTRLB |= USART_TXEN_bm | USART_RXMODE_NORMAL_gc;
  PORTB.DIR |= (1 << TX_PIN_bp);
  PORTB.PINCONFIG |= PORT_PULLUPEN_bm;
  USART3.CTRLA |= USART_RXCIE_bm;

  stdout = &new_std_out; // Redirecting stdout to USART
}

void usart_usb_transmit(char c) {
  while (!(USART3.STATUS & USART_DREIF_bm)) {
    ;
  }
  USART3.TXDATAL = c;
}

void usart_usb_transmit_char_array(uint8_t addEndLine, char string[],
                                   uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    usart_usb_transmit(string[i]);
  }
  if (addEndLine)
    usart_usb_transmit('\n');
}

char usart_usb_receive() {
  while (!(USART3.STATUS & USART_RXCIF_bm)) // Not unread data in receiver
    ;
  return USART3.RXDATAL;
}

int usart_usb_transmit_printf(char c, FILE *stream) {
  usart_usb_transmit(c);
  return 0;
}

/* Generic USART files */

void usart_init(USART_t *usart_nr, PORT_t *usart_port, uint8_t tx_bp,
                uint8_t rx_bp) {
  usart_nr->BAUD = 9600;
  usart_nr->CTRLB |= USART_TXEN_bm | USART_RXMODE_NORMAL_gc;
  usart_port->DIR |= (1 << tx_bp);
  usart_port->PINCONFIG |= PORT_PULLUPEN_bm;
}

void usart_transmit_char(USART_t *usart_nr, char c) {
  while (!(usart_nr->STATUS & USART_DREIF_bm))
    ;
  usart_nr->TXDATAL = c;
}

void usart_transmit_string(USART_t *usart_nr, char *string,
                           usart_char_transmitter transmit_char) {
  for (uint8_t i = 0; string[i] != '\0'; i++) {
    transmit_char(usart_nr, string[i]);
  }
}

/* rx-interrupt with some handling. see main*/
ISR(USART3_RXC_vect) {
  char tmp = USART3.RXDATAL;
  switch (tmp) {
  case '<':
    marker_pos = 0;
    break;
  case '>':
    usb_message_ready = 1;
    usb_message[marker_pos] = 0; // Null-terminate the message
    break;
  default:
    if (marker_pos < sizeof(usb_message) - 1) {
      usb_message[marker_pos] = tmp;
      marker_pos++;
    }
    break;
  }
}
