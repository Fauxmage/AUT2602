

#include "adc.h"
#include "config.h"
#include <avr/io.h>
#include <xc.h>
#define F_CPU 4000000UL
#include <util/delay.h>

#include <avr/interrupt.h>

#define SAMP_NUM 8
#define SAMP_LEN 8
#define SCALING_FACTOR 4096
#define KELVIN 273

void adc_init() { ADC0.CTRLA |= ADC_ENABLE_bm; }

void adc_en_freerun() { ADC0.CTRLA |= ADC_FREERUN_bm; }

void adc_vref(VREF_REFSEL_t ref) { VREF_ADC0REF |= ref; }

void adc_input_sel(ADC_MUXPOS_t mux) { ADC0.MUXPOS = mux; }

void adc_init_delay(ADC_INITDLY_t delay) { ADC0.CTRLD |= delay; }

void adc_sampling(ADC_SAMPNUM_t samp_len, register8_t samp_num) {
  ADC0.CTRLB |= samp_num;
  ADC0.SAMPCTRL = samp_len;
}

void adc_clock(ADC_PRESC_t clck) { ADC0.CTRLC = clck; }

uint16_t adc_get_data() {
  while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
    ;
  return ADC0.RES;
}

void init_temp_sensor() {
  adc_vref(VREF_REFSEL_2V048_gc);
  adc_clock(ADC_PRESC_DIV16_gc);
  adc_input_sel(ADC_MUXPOS_TEMPSENSE_gc);
  adc_en_freerun();
  adc_init_delay(ADC_INITDLY_DLY128_gc);
  adc_sampling(SAMP_LEN, ADC_SAMPNUM_ACC16_gc);
  adc_init();
  ADC0.COMMAND |= ADC_STCONV_bm;
}

uint16_t adc_read_temp() {
  //------  Following code is from AVRDB128DBXX  ------//
  uint16_t sigrow_slope =
      SIGROW.TEMPSENSE0; // Read unsigned gain/slope from signature row
  uint16_t sigrow_offset =
      SIGROW.TEMPSENSE1; // Read unsigned offset from signature row
  uint16_t adc_reading = (adc_get_data() / SAMP_NUM);
  uint32_t temp = sigrow_offset - adc_reading;
  temp *= sigrow_slope;       // Result can overflow 16-bit variable
  temp += SCALING_FACTOR / 2; // Ensures correct rounding on division below
  temp /= SCALING_FACTOR;     // Round off to nearest degree in Kelvin
  return temp - KELVIN;
}
