#include "adc.h"

#define SAMP_NUM 16
#define SAMP_LEN 8 
#define SCALING_FACTOR 4096


void adc_init(void){
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

void adc_en_freerun(void){
	ADC0.CTRLA |= ADC_FREERUN_bm;
}

void adc_vref(uint8_t ref){
	VREF_ADC0REF |= ref;
}

void adc_input_sel(uint8_t mux){
	ADC0.MUXPOS = mux;
}
 
void adc_init_delay(uint8_t delay){
	ADC0.CTRLD |= delay;
}

void adc_sampling(register8_t samp_len){
	ADC0.CTRLB |= ADC_SAMPNUM_ACC4_gc;
	ADC0.SAMPCTRL = samp_len;
}

void adc_clock(ADC_PRESC_t clck){
	ADC0.CTRLC = clck;
}

uint16_t adc_get_data(void){
	while(!(ADC.INTFLAGS & ADC_RESRDY_bm));
	return ADC0.RES;
}

void init_temp_sensor(void){	
	adc_en_freerun();
	adc_vref(VREF_REFSEL_2V048_gc);
	adc_input_sel(ADC_MUXPOS_TEMPSENSE_gc);
	adc_init_delay(ADC_INITDLY_DLY128_gc);
	adc_sampling(SAMP_NUM);
	adc_clock(ADC_PRESC_DIV16_gc);
	adc_init();

	ADC0.COMMAND |= ADC_STCONV_bm;
}


uint16_t adc_read_temp(void){
	//------  Following code is from AVRDB128DBXX  ------//
	uint16_t sigrow_slope = SIGROW.TEMPSENSE0; // Read unsigned gain/slope from signature row
	uint16_t sigrow_offset = SIGROW.TEMPSENSE1; // Read unsigned offset from signature row
	uint16_t adc_reading = (adc_get_data() / SAMP_NUM);
	uint32_t temp = sigrow_offset - adc_reading;
	temp *= sigrow_slope; // Result can overflow 16-bit variable
	temp += SCALING_FACTOR / 2; // Ensures correct rounding on division below
	temp /= SCALING_FACTOR; // Round off to nearest degree in Kelvin
	// uint16_t temperature_in_K = temp;
	int16_t temperature_in_C = temp - 273;
	return temperature_in_C = temp - 273;
}
