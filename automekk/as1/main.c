/*
* Ulrik Brochmann, ubr004@uit.no
*/
#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


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

    // Activates LEDs one by one, then deactivates one by one, repeatedly
    while (1){
        uint8_t ctr = 0;
        for (ctr = 0; ctr < 4; ctr++){
            PORTC.OUT ^= (1 << ctr);
            _delay_ms(500);
		    if (ctr == 4){
			    ctr = 0;
		    }
        }
    }
}


// Used for problem 2c
void led_blink(){
    // Toggles diode every 300ms on/off
    PORTC.OUTTGL = (1 << 3);
    _delay_ms(300);
}

// Problem 2c, press switches SW1-SW3 to light up diodes D0-D3, a combination to make D3 blink.
void switches_diodes_2c(){
    // Set to input
    PORTD.DIRCLR |= (1 << 0) | (1 << 1) | (1 << 2); 

    // Enable pull up/invert on SW1-SW3
    PORTD.PIN0CTRL |= PORT_PULLUPEN_bm | PORT_INVEN_bm;            
    PORTD.PIN1CTRL |= PORT_PULLUPEN_bm | PORT_INVEN_bm;            
    PORTD.PIN2CTRL |= PORT_PULLUPEN_bm | PORT_INVEN_bm;


    // Set diodes to outpu
    PORTC.DIRSET = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    PORTC.PINCTRLSET |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    while (1) {
        // Toggles blinking for D3
        led_blink();
        
        // Switch SW1-SW3 states
        uint8_t switch1 = !(PORTD.IN & (1 << 0));
        uint8_t switch2 = !(PORTD.IN & (1 << 1));
        uint8_t switch3 = !(PORTD.IN & (1 << 2)); 

        // Update diode states based on switch states
        if (switch1) {
            PORTC.OUTSET = (1 << 0); // Turn on diode D0
        } else {
            PORTC.OUTCLR = (1 << 0); // Turn off diode D0
        }
        if (switch2) {
            PORTC.OUTSET = (1 << 1); // Turn on diode D1
        } else {
            PORTC.OUTCLR = (1 << 1); // Turn off diode D1
        }
        if (switch3) {
            PORTC.OUTSET = (1 << 2); // Turn on diode D2
        } else {
            PORTC.OUTCLR = (1 << 2); // Turn off diode D2
        }

    }
}


// Problem 2d, D0-D2 toggles on/off when activating SW1-SW3.
void switches_diodes_2d(){
    PORTD.DIRCLR = (1 << 0) | (1 << 1) | (1 << 2);
    PORTD.PIN0CTRL |= PORT_PULLUPEN_bm;
    PORTD.PIN1CTRL |= PORT_PULLUPEN_bm;
    PORTD.PIN2CTRL |= PORT_PULLUPEN_bm;


    // Set diodes to output and invert them
    PORTC.PINCONFIG |= PORT_INVEN_bm;
    PORTC.DIR = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    PORTC.PINCTRLSET |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    while (1){
        // Switch SW1-SW3 states
        uint8_t switch1 = !(PORTD.IN & (1 << 0));
        uint8_t switch2 = !(PORTD.IN & (1 << 1));
        uint8_t switch3 = !(PORTD.IN & (1 << 2));

        // Check SW1 state
        if (switch1) {
            // Toggle D0
            PORTC.OUTTGL = (1 << 0);
            _delay_ms(15); // Debounce delay
            // Wait for SW to change state
            while (switch1){
                switch1 = !(PORTD.IN & (1 << 0));
            }
        }
        // Check SW2 state
        if (switch2) {
            // Toggle D3
            PORTC.OUTTGL = (1 << 1);
            _delay_ms(15); // Debounce delay
            // Wait for SW to change state
            while (switch2){ 
                switch2 = !(PORTD.IN & (1 << 1));
            }
        }
        // Check SW3 state
        if (switch3){
            // Toggle D2
            PORTC.OUTTGL = (1 << 2);
            _delay_ms(15); // Debounce delay
            // Wait for SW to change state 
            while (switch3){
                switch3 = !(PORTD.IN & (1 << 2));
            }
        }
        // additional debounce delay, toggle is less "jittery" 
        _delay_ms(10);
    }
}

// Setting up ports and interrupts
void isr_Setup() {
    PORTD.DIRCLR = (1 << 0) | (1 << 1) | (1 << 2);
    // Enable pullup and fallingedge interrupt
    PORTD.PIN0CTRL |= PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
    PORTD.PIN1CTRL |= PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
    PORTD.PIN2CTRL |= PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;

    PORTC.DIRSET = (1 << 0) | (1 << 1) | (1 << 2);
    PORTC.OUTCLR = (1 << 0) | (1 << 1) | (1 << 2);
}

// Use a volatile variable to keep track which SW calls for interrupt, then toggle appropriate LED.
volatile uint8_t led_flags = 0;
ISR(PORTD_PORT_vect){

    // Switch SW1-SW3 states
    uint8_t switch1 = !(PORTD.IN & (1 << 0));
    uint8_t switch2 = !(PORTD.IN & (1 << 1));
    uint8_t switch3 = !(PORTD.IN & (1 << 2));


    // Toggles LED, cleares INT flag(s).
    if (switch1) {
        PORTC.OUTTGL = (1 << 0);
        _delay_ms(1000);
        PORTD.INTFLAGS = (1 << 0);
    }
    if (switch2) {
        PORTC.OUTTGL = (1 << 1);
        _delay_ms(2000);
        PORTD.INTFLAGS = (1 << 1);
    }
    if (switch3) {
        PORTC.OUTTGL = (1 << 2); 
        _delay_ms(3000);
        PORTD.INTFLAGS = (1 << 2);
    }
}


int main(void){
    // Initialiserer alt for interrupts
    isr_Setup();


	/*Oppgave 2a, blinker lysene ved forskjellig delay
	 *kommenter ut funksjonen for å teste.
	 */
	blink_diodes_0_3_2a();
	

	/*Oppgave 2b aktiverer lysene en om gangen, deretter slår av
     *lysene en etter og, gjentas uendelig.
	 *kommenter ut funksjonen for å teste.
	 */
	// for_loop_diodes_2b();

	
    /*Oppgave 2c ferdig, SW1-SW3 aktiverer lysene D0-D2
     *Diode D3 er satt til å blinke uendelig 0.3s delay.
     *kommeter ut funksjonen for å teste.
     */
	//switches_diodes_2c();

    
    /*Oppgave 2d, toggle dioder D0-D2 ved hjelp av SW1-SW3
     *kommenter ut funksjonen for å teste.
     */
    switches_diodes_2d();


    sei();
    while (1){
        /*
         *Oppgave 2e, kjører diode loop, interrupter for å toggle 
         *diodene D0-D3 i en liten periode basert på hvilken SW 
         *som aktiveres.
         *kommenter ut funksjonen for å teste.
         */
        //for_loop_diodes_2b();
    }
}