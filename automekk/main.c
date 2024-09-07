/*
 * File:   main.c
 * Author: ulrikjohnsen
 *
 * Created on August 28, 2023, 2:18 PM
 */

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t LED_state = 0;

// Function for problem 2a, init the LED on PB3 by setting the state to HIGH
void init_led() {
    PORTB.DIRSET = (1 << 3);
}


// Function for problem 2b, toggle the output with a specified delay in the main fucntion
void led_blink(){
    PORTB.OUTTGL = (1 << 3);
}


// Function for problem 2d), make the LED light up when SW0 is held down
void init_button(){
    PORTB.DIRCLR = (1 << 2); // Set Pin 2 of Port B as an input
    PORTB.PIN2CTRL |= PORT_PULLUPEN_bm; // Enable the pull-up resistor on Pin 2

}


ISR(PORTB_PORT_vect){
    // XOR the state of the LED

     // Update the LED pin based on the updated state
    if (LED_state ^= 1) {
        PORTB.OUTSET = (1 << 2); // Turn on the LED
    } 
    else {
        PORTB.OUTCLR = (1 << 2); // Turn off the LED
    }

    // Clear the interrupt flag for the associated pin
    PORTC.INTFLAGS |= PIN2_bm;


}


int main(void) {
    init_led();
    init_button();
    int toggle_status = 0;


    PORTC.PIN2CTRL |= PORT_ISC_FALLING_gc; // Configure falling-edge trigger
    PORTC.INTFLAGS |= PORT_INT0_bm;


    sei();
    while (1) {

        init_led();
        /*
        Problem 1a) Make the LED light up
        */

        // init_led();


        
        /*
        Problem 2b) The LED on PB3 will blink with 1000ms delay
        */

        // led_blink();
        // _delay_ms(1000);
        



        /*Problem 2c) What is a pull-up? 
        */



        
        /*
        Problem 2d) Make LED light up when button is pushed down
        */

        // // If button is pushed down, then set PB3 to HIGH
        // if (PORTB.IN & (1 << 2)){
        //     PORTB.OUTSET = (1 << 3);
        // }

        // // If button is not pushed down, then set PB3 to LOW
        // else{
        //     PORTB.OUTCLR = (1 << 3); 
        // }

        


        /*
        Problem 2e) Toggle light on and off
        */

        // // Check if the button is pressed
        // if (!(PORTB.IN & PIN2_bm)){
        //     // Debounce delay
        //     _delay_ms(100); 
        //     if (!(PORTB.IN & PIN2_bm)){
        //         // Button is still pressed after debounce
        //         if (toggle_status == 0){
        //             toggle_status = 1;
        //         } 
        //         else{
        //             toggle_status = 0;
        //         }

        //         // Wait for button release
        //         while (!(PORTB.IN & PIN2_bm)); 
        //     }
        // }

        // // Control the LED based on toggle_status
        // if (toggle_status == 0){
        //     PORTB.OUTSET = (1 << 3); 
        // } 
        // else{
        //     PORTB.OUTCLR = (1 << 3);
        // }

    }

    
    return 0;
}