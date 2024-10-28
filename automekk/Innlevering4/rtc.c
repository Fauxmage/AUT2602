#include "rtc.h"

// Set RTC period
void rtc_set_period(uint32_t period){
	RTC.PER = period;
}

// Enable/Disable PIT (1/0)
void rtc_pit_enable(uint8_t pit_en){
	if(pit_en){
		RTC.PITCTRLA |= RTC_PIT_bm;
	}
	else{
		RTC.PTCTRLA &= ~RTC_PIT_bm;
	}
}


void rtc_set_cmp(uint32_t cmp){
	RTC.CMP = cmp;
}


void rtc_set_interrupt(uint8_t interrupt){
	RTC.INTCTRL = interrupt;
}


void rtc_set_prescaler(uint8_t prescaler){
	while(RTC.STATUS & RTC_CTRLABUSY_bm){
		//Two RTC clock cycle delay
		_delay_ms(5);
	}
	CTRLA.PRESCALER = prescaler;
}


// Internal clock config
void rtc_clk_sel(uint8_t clk_select){
	// RTC.CLKSEL = clk_select;
	// Wait for control reigister sync to avoid issues
	while (RTC.STATUS & RTC_CTRLABUSY_bm);
	
	// Check later on how to handle values for these, CLKSEL may even do this automatically...
	if(clk_select == 0){
		// Activate by RTC.CLKSEL = 0x00?
		rtc_int_clk_ctrl();
	}
	else if(clk_select == 1){
		// Activate by RTC.CLKSEL = 0x02?
		rtc_ext_clk_ctrl();
	}
}


void rtc_int_clk_ctrl(){
	CLKCTRL.OSC32KCTRLA |= CLKCTRL_ENABLE_bm;     // Enable internal clock
	CLKCTRL.XOSC32KCTRLA &= ~(CLKCTRL_ENABLE_bm); // Disable external clock
}

void rtc_ext_clk_ctrl(){
	CLKCTRL.OSC32KCTRLA &= ~(CLKCTRL_ENABLE_bm);  // Disable internal clock
	CLKCTRL.XOSC32KCTRLA |= CLKCTRL_ENABLE_bm;     // Enable external clock
}


// Enable/disable RTC (1/0)
void rtc_init(uint8_t enable, uint8_t clk_sel){
	// Configure RTC settings before enable
	clk_sel = 0; // Init to 0 to make sure no funny business
	
	rtc_set_period(0);
	rtc_pit_enable(0);
	rtc_set_cmp(0);
	rtc_set_interrupt(0);
	rtc_clk_sel(clk_sel);
	rtc_set_prescaler(RTC_PRESCALER_DIV32768_gc);

	if(enable){
		RTC.CTRLA |= RTC_RTCEN_bm;
	}
	else{
		RTC.CTRLA &= ~RTC_RTCEN_bm;
	}
}


/*
 * To configure the CLK_RTC, follow these steps: 
 * 1. Configure the desired oscillator to operate as required, in the Clock Controller (CLKCTRL) peripheral. 
 * 2. Write the Clock Select (CLKSEL) bit field in the Clock Selection (RTC.CLKSEL) register accordingly. 
 * The CLK_RTC clock configuration is used by both RTC and PIT functionalities.
 * */
