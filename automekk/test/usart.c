#define F_CPU 4000000UL
#define B_RATE(BAUD) ((64 * F_CPU) / (16 * (float)BAUD) + 0.5)

#include "usart.h"

volatile char transmit_buffer[100];
volatile uint8_t next = 0;
volatile uint8_t last = 0;

char usb_message[256];
volatile uint8_t marker_pos;
volatile uint8_t usb_message_ready;

void usart_usb_init(uint16_t baud) {
  // Set baud rate
  USART3.BAUD = B_RATE(baud);
  // Enable TX and RX
  USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
  // Set TX pin as output
  PORTB.DIR |= (1 << TX_PIN_bp);
  // Enable RX complete interrupt (if necessary)
  // USART3.CTRLA |= USART_RXCIE_bm;

  // Redirect stdout to the USART stream
  stdout = &new_std_out;
}

void usart_usb_transmit(char c) {
  // Wait until the transmit buffer is empty
  while (!(USART3.STATUS & USART_DREIF_bm))
    ;
  // Transmit the character
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
  // Wait for a character to be received
  while (!(USART3.STATUS & USART_RXCIF_bm))
    ;
  return USART3.RXDATAL;
}

void usart_transmit_char(USART_t *usart_nr, char c) {
  // Wait until the transmit buffer is empty
  while (!(usart_nr->STATUS & USART_DREIF_bm))
    ;
  // Transmit the character
  usart_nr->TXDATAL = c;
}

uint8_t usart_usb_transmit_printf(char c, FILE *stream) {
  // Wait until the transmit buffer is empty
  while (!(USART3.STATUS & USART_DREIF_bm))
    ;
  // Transmit the character
  usart_usb_transmit(c);
  return 0;
}

void usart_transmit_string(USART_t *usart_nr, char *string,
                           usart_char_transmitter transmit_char) {
  for (uint8_t i = 0; string[i] != '\0'; i++) {
    transmit_char(usart_nr, string[i]);
  }
}
