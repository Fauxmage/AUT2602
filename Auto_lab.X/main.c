/*
 * File:   main.c
 * Author: ulrikjohnsen
 *
 * Created on August 28, 2023, 2:18 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>


void init_led(){
    PORTB.DIR |= (1<<3);
}


int main(void) {
    
    
    init_led();
    while(1){
        init_led();
        
    }
}
