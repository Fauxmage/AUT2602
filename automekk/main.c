#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Defines to help with more readable code
#define LED_PIN 3 
#define BUTTON_PIN 2


// Function for initializing LEDs
void init_led() {
    PORTB.DIR |= (1 << LED_PIN); // Set LED as output
    PORTB.PINCONFIG |= PORT_INVEN_bm; // Invert so that 0 = 1, 1 = 0. 
}

void led_blink(){
    PORTB.OUTTGL = (1 << 3);
}


void init_button(){
    PORTB.DIR |= (1 << BUTTON_PIN); // Set Pin 2 of Port B as an input
    PORTB.PINCONFIG |= PORT_INVEN_bm; // Invert output 
    PORTB.PINCONFIG |= PORT_PULLUPEN_bm; // Enable pullup
}


// Problem 2a, blink diodes D0-D3 in different ways.
void blink_diodes_0_3_2a(){
    // Set D0-D3 as outputs.
    PORTC.DIRSET = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    PORTC.PINCONFIG |= PORT_INVEN_bm;
	
	while (1){
		PORTC.OUT ^= (1 << 0);
		_delay_ms(50);

		PORTC.OUT ^= (1 << 1);
		_delay_ms(150);

		PORTC.OUT ^= (1 << 2);
		_delay_ms(300);

		PORTC.OUT ^= (1 << 3);
		_delay_ms(600);
	}
}


// Problem 2b, for loop that actives diodes one by one.
void for_loop_diodes_2b(){
     // Set D0-D3 as outputs.
    PORTC.DIRSET = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    // Invert 
    PORTC.PINCONFIG |= PORT_INVEN_bm;
	

	uint8_t ctr = 0;
    for (ctr = 0; ctr < 4; ctr++){
        PORTC.OUT ^= (1 << ctr);
        _delay_ms(100);
		if (ctr >= 3){
			ctr = 0;
		}
    }
}

// Problem 2c, D0-D2 lights up when activating SW1-SW3, D3 blinks
void switches_diodes_2c(){
    PORTD.DIRCLR = (1 << 0) | (1 << 1) | (1 << 2);
    
    PORTD.PIN0CTRL |= PORT_PULLUPEN_bm; 
    PORTD.PIN1CTRL |= PORT_PULLUPEN_bm; 
    PORTD.PIN2CTRL |= PORT_PULLUPEN_bm;

    // Check the state of SW1-SW3
    uint8_t switches = (PORTD.IN & ((1 << 0) | (1 << 1) | (1 << 2)));
    switch (switches){
        case (1 << 0):
			PORTC.OUT ^= (1 << 0);
            break;
        case (1 << 1):
			PORTC.OUT ^= (1 << 1);
            break;
        case (1 << 2):
			PORTC.OUT ^= (1 << 2);			
			break;
		//case (()):
        //default:
        //    PORTB.OUTCLR = (0 << 0) | (0 << 1) | (0 << 2);
        //    break;
    }
}


/* UNCOMMENT WHEN MOVING ONTO ISR 
// Problem 2e, TO-DO: EVERYTHING
ISR(PORTB_PORT_vect){
    // XOR the state of the LED
	
     // Update the LED pin based on the updated state
    if (LED_state ^= 1) {
        PORTC.OUTSET = (1 << 2); // Turn on the LED
    } 
    else {
        PORTC.OUTCLR = (1 << 2); // Turn off the LED
    }
    // Clear the interrupt flag for the associated pin
    PORTC.INTFLAGS |= PIN2_bm;
}
*/

int main(void) {
    init_led();
    init_button();
    
	/*Oppgave 2a ferdig, blinker lysene ved forskjellig delay
	 *kommenter ut funksjonen for å teste.
	 */
	// blink_diodes_0_3_2a();
	

	/*Oppgave 2b ferdig, aktiverer lysene en og en 
	 *kommenter ut funksjonen for å teste.
	 */
	// for_loop_diodes_2b();
	
	switches_diodes_2c();	
    sei();
    while (1){
    }
}
