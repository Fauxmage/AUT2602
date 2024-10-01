#ifndef ADC_H
#define ADC_H
#define F_CPU 4000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void adc_init();
void adc_en_freerun();
void adc_vref(VREF_REFSEL_t ref);
void adc_input_sel(ADC_MUXPOS_t mux);
void adc_init_delay(ADC_INITDLY_t delay);
void adc_sampling(ADC_SAMPNUM_t samp_len, register8_t samp_num);
void adc_clock(ADC_PRESC_t clck);
void init_temp_sensor();

uint16_t adc_get_data();
uint16_t adc_read_temp();

#endif /* ADC_H_ */
