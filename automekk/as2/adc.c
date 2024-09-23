#include "adc.h"
#include "config.h"
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>

#define SAMP_NUM 16
#define SAMP_LEN 8 
#define SCALING_FACTOR 4096
#define KELVIN 273


void adc_init(){
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

void adc_en_freerun(){
	ADC0.CTRLA |= ADC_FREERUN_bm;
}

void adc_vref(VREF_REFSEL_t ref){
	VREF_ADC0REF |= ref;
}

void adc_input_sel(ADC_MUXPOS_t mux){
	ADC0.MUXPOS = mux;
}
 
void adc_init_delay(ADC_INITDLY_t delay){
	ADC0.CTRLD |= delay;
}

void adc_sampling(ADC_SAMPNUM_t samp_len, register8_t samp_num){
	ADC0.CTRLB |= samp_num;
	ADC0.SAMPCTRL = samp_len;
}

void adc_clock(ADC_PRESC_t clck){
	ADC0.CTRLC = clck;
}

uint16_t adc_get_data(){
	while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	return ADC0.RES;
}


// Initialize the internal temperature sensor on AVR
void init_temp_sensor(){
	// Select internal voltage reference 2.084V
	adc_vref(VREF_REFSEL_2V048_gc);

	// ADC clock set to 250kHz
	adc_clock(ADC_PRESC_DIV16_gc);

	// Select temperature sensor as an input
	adc_input_sel(ADC_MUXPOS_TEMPSENSE_gc);

	// Delay initialization 
	adc_init_delay(ADC_INITDLY_DLY128_gc);

	// Set ADC sample length and how many samples to accumualte 
	adc_sampling(SAMP_LEN, ADC_SAMPNUM_ACC16_gc);

	// Enable freerun mode
	adc_en_freerun();

	// Initialize the ADC after configuring it
	adc_init();

	// Start conversion
	ADC0.COMMAND |= ADC_STCONV_bm;
}

/*
 *	The following code is taken from the AVR128DBxx datasheet
 *	Slight modifications to variable names only.
 */
int16_t adc_read_temp(){
	uint16_t sigrow_slope = SIGROW.TEMPSENSE0;
	uint16_t sigrow_offset = SIGROW.TEMPSENSE1;
	uint16_t adc_reading = (adc_get_data()/SAMP_NUM);
	uint32_t temp = sigrow_offset - adc_reading;
	temp *= sigrow_slope;
	temp += SCALING_FACTOR / 2;
	temp /= SCALING_FACTOR;
	return temp - KELVIN;
}
