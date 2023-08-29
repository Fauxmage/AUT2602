/*
 * File:   main.c
 * Author: ulrikjohnsen
 *
 * Created on August 28, 2023, 2:18 PM
 */

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>



// Function for problem 2a, init the LED on PB3 by setting the state to HIGH
void init_led() {
    PORTB.DIRSET = (1 << 3);
}


// Function for problem 2b, toggle the output with a specified delay in the main fucntion
void led_blink(){
    PORTB.OUTTGL = (1 << 3);
}

void init_button(){
    PORTB.DIRCLR = (1 << 2); // Set Pin 2 of Port B as an input
    PORTB.PIN2CTRL |= PORT_PULLUPEN_bm; // Enable the pull-up resistor on Pin 2

}


int main(void) {
    init_led();
    init_button();
    
    while (1) {

        /*
        // OPPGAVE 2a) 
        init_led();
        */
       

       /*
       // Problem 2b) The LED on PB3 will blink with 1000ms delay
       led_blink();
       _delay_ms(1000);
        */



        /*Problem 2c) What is a pull-up? 
        */



       // Problem 2d) Make LED light up when button is pushed down
       // If button is pushed down, then set PB3 to HIGH
        if (PORTB.IN & (1 << 2)){
            PORTB.OUTSET = (1 << 3);
        }

        // If button is not pushed down, then set PB3 to LOW
        else{
            PORTB.OUTCLR = (1 << 3); 
        }



    }
    
    return 0;
}

// // Check if the button on Pin 2 is pressed
// if (!(PORTB.IN & (1 << BUTTON_PIN))) {
//     // Button is pressed, turn on the LED
//     PORTB.OUTSET = (1 << LED_PIN); // Set Pin 3 of Port B to HIGH
// } else {
//     // Button is not pressed, turn off the LED
//     PORTB.OUTCLR = (1 << LED_PIN); // Clear Pin 3 of Port B (set to LOW)
// }

/*
void init_button() {
    PORTB.DIRCLR = (1 << 2); // Set Pin 2 of Port B as an input
    PORTB.PIN2CTRL |= PORT_PULLUPEN_bm; // Enable the pull-up resistor on Pin 2
}
*/