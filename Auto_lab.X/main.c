/*
 * File:   main.c
 * Author: ulrikjohnsen
 *
 * Created on August 28, 2023, 2:18 PM
 */

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN 2
#define LED_PIN 3

void init_led() {
    PORTB.DIRSET = (1 << LED_PIN); // Set Pin 3 of Port B as an output
}

void init_button() {
    PORTB.DIRCLR = (1 << BUTTON_PIN); // Set Pin 2 of Port B as an input
    PORTB.PIN2CTRL |= PORT_PULLUPEN_bm; // Enable the pull-up resistor on Pin 2
}

int main(void) {
    init_led();
    init_button();
    
    while (1) {
        // Check if the button on Pin 2 is pressed
        if (!(PORTB.IN & (1 << BUTTON_PIN))) {
            // Button is pressed, turn on the LED
            PORTB.OUTSET = (1 << LED_PIN); // Set Pin 3 of Port B to HIGH
        } else {
            // Button is not pressed, turn off the LED
            PORTB.OUTCLR = (1 << LED_PIN); // Clear Pin 3 of Port B (set to LOW)
        }
    }
    
    return 0;
}

