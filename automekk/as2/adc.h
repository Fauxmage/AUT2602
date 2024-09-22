#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init(void);
void adc_en_freerun(void);
void adc_vref(uint8_t ref);
void adc_input_sel(uint8_t mux);
void adc_init_delay(uint8_t delay);
void adc_sampling(register8_t samp_len);
void adc_clock(ADC_PRESC_t clck);
void init_tmp_sensor(void);

uint16_t adc_get_data(void);
uint16_t adc_read_temp(void);


#endif /* ADC_H */
