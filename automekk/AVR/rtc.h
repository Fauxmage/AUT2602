#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* |---- CONFIGURING RTC ----|
 * 1. Set the compare value in the Compare (RTC.CMP) register, and/or the overflowoverflow value in the Period (RTC.PER) register.    
 * 2. Enable the desired interrupts by writing to the respective interrupt enable bits (CMP, OVF) in the Interrupt Control (RTC.INTCTRL) register.
 * 3. Configure the RTC internal prescaler by writing the desired value to the Prescaler (PRESCALER) bit field in the Control A (RTC.CTRLA) register.
 * 4. Enable the RTC by writing a ‘1’ to the RTC Peripheral Enable (RTCEN) bit in the RTC.CTRLA register.
 *
 * AVR128DB48 Datasheet, 26.4.1.2, page 366.
 */

void rtc_set_period(uint32_t period);
void rtc_pit_en(uint8_t pit_en);
void rtc_set_cmp(uint32_t cmp);
void rtc_set_interrupt(uint8_t interrupt);
void rtc_set_prescaler(uint8_t prescaler);

// Internal clock
void rtc_clk_sel(uint8_t clk_select);

// External clock
void rtc_int_clk_ctrl();
void rtc_ext_clk_ctrl();

void rtc_init(uint8_t enable, uint8_t clk_sel);
#endif /* RTC_H_ */
