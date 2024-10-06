#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>


// Enable "Run Standby"
void clk_run_stdby(uint8_t en_stdby);
void clk_select(uint8_t clk);


// Main clock oscillator
void clk_mc_osc();
void init_led();
void configure_main_clock_16MHz();
void init_timer_tca0(uint16_t period, uint16_t div);
void clock_init_16MHz();
void scale_frequency(uint16_t start_freq, uint16_t end_freq, uint16_t div);
void buzz();
void t_clock_init(uint16_t period, uint16_t div);

#endif /* TIMER_H */
