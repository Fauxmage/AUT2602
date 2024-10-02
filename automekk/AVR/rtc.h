#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* |---- CONFIGURING RTC ----|
 * 1. Set the compare value in the Compare (RTC.CMP) register, and/or the
 * overflow value in the Period (RTC.PER) register.
 * 2. Enable the desired interrupts by writing to the respective interrupt
 * enable bits (CMP, OVF) in the Interrupt Control (RTC.INTCTRL) register.
 * 3. Configure the RTC internal prescaler by writing the desired value to the
 * Prescaler (PRESCALER) bit field in the Control A (RTC.CTRLA) register.
 * 4. Enable the RTC by writing a ‘1’ to the RTC Peripheral Enable (RTCEN) bit
 * in the RTC.CTRLA register.
 *
 * AVR128DB48 Datasheet, 26.4.1.2, page 366.
 */

void rtc_init();
void rtc_set_period(uint32_t period);
void rtc_set_cmp(uint32_t compare);
void rtc_set_interrupt(uint8_t interrupt);

#endif /* RTC_H_ */
