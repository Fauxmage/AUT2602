#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init();
void adc_set_freerun();
void adc_vref(uint8_t ref);
void adc_input_sel(uint8_t mux);
void adc_init_delay(uint8_t delay);
void adc_sampling(register8_t smp_len);
void adc_clock(ADC_PRESC_t clck);
void init_tmp_sensor();

uint16_t adc_get_data();
uint16_t adc_read_tmp();


#endif /* ADC_H */
