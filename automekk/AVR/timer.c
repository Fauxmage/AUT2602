#include "timer.h"
#include "usart.h"

void clk_run_stdby(uint8_t en_stdby){
	if (en_stdby) {
        CLKCTRL.MCLKCTRLB |= CLKCTRL_RUNSTDBY_bm;  // Enable run in standby
    } else {
        CLKCTRL.MCLKCTRLB &= ~CLKCTRL_RUNSTDBY_bm; // Disable run in standby
    }
}

// Main clock oscillator
void clk_mc_osc(){
	ccp_write_io((void *) &CLKCTRL.OSCHFCTRLA, (7 << CLKCTRL_FRQSEL_0_bp));
}

void clock_init_16MHz(){
    // Enable 16MHz clock
    ccp_write_io((void *) &CLKCTRL.MCLKCTRLA, 0x0); }

void init_timer_tca0(uint16_t period, uint16_t div){
    TCA0.SINGLE.PER = period; //65535;  
    // Enable overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    // Start timer with no prescaling
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | div;
}

// Initialiser LED 
void init_led(){
   PORTB.DIRSET = (1 << 3);
}

ISR(TCA0_OVF_vect) {
	PORTB.OUTTGL = (1 << 3); // Toggle LED
	//
	// PORTF.OUTTGL = (1 << 2);
	
    TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;  // Clear flag
}


void scale_frequency(uint16_t start_freq, uint16_t end_freq, uint16_t div){
    // Calculate start & end "PER" values from prescaler input
    uint32_t start_per = (16000000 / ((uint32_t)div * (uint32_t)start_freq));
    uint32_t end_per = (16000000 / ((uint32_t)div * (uint32_t)end_freq));

    for (uint16_t per = start_per; per >= end_per; per--) {
		printf("Per %u\n", per);
		// Set new PER value
        TCA0.SINGLE.PER = per;  
        _delay_ms(10);  
    }
}


void buzz(){
	PORTF.DIRSET = (1 << 2);
}


void t_clock_init(uint16_t period, uint16_t div){	
	clk_run_stdby(1);
	clk_mc_osc();
	clock_init_16MHz();
	init_led();
	buzz();
	init_timer_tca0(period, div);
}
