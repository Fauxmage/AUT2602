#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>


// Enable "Run Standby"
void clk_run_stdby(uint8_t en_stdby);
void clk_mc_osc();
// Init LED for blinking with ISR
void init_led();
// Initialize timer TCA0
void init_timer_tca0(uint16_t period, uint16_t div);
void clock_init_16MHz();
// Scale frequency 1-5kHz
void scale_frequency(uint16_t start_freq, uint16_t end_freq, uint16_t div);
// Enable buzzer
void buzz();
// Scale buzzer with for loops
void scale_buzz(uint16_t start_freq, uint16_t end_freq, uint16_t div);
// Init function called in main.c
void t_clock_init(uint16_t period, uint16_t div);

#endif /* TIMER_H */
