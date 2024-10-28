#include "pwm.h"
#include <avr/io.h>


// NB! As of now, only task a) has been finished.

/* Initialize singleslope microservo with TCA0 */
void init_pwm(uint16_t per, uint16_t p){
	/* Set PORTMUX to PORTE */
	PORTMUX.TCAROUTEA |= PORTMUX_TCA0_PORTE_gc; // (0x04 << 0);

	/* Set as PE0 as output, invert */
	PORTE.DIR |= (1 << 0);
	PORTE.PIN0CTRL |= PORT_INVEN_bm;
	
	/* Disable TCA0 before configuring */
    TCA0.SINGLE.CTRLA = 0x00;
	/* Enable wavegen mode singleslope and enable cmp channels for PE0 */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
	/* Set PWM period and position */
	TCA0.SINGLE.PER = per;
	
	/* Set position for microservo */
	pwm_set_p(p);
	/* Set the prescaler and enable TCA0 */
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc | TCA_SINGLE_ENABLE_bm;
}

/* Set the position of microservo */
void pwm_set_p(uint16_t p){
	TCA0.SINGLE.CMP0BUF = p;
}

void init_leddies(uint16_t per, uint16_t p){
	/* Set LED0-2 as outputs, invert */
	PORTC.DIR = (1 << 0) | (1 << 1) | (1 << 2);
    PORTC.PINCONFIG |= PORT_INVEN_bm;
	
	/* Disable TCA0 before configuring */
    TCA0.SINGLE.CTRLA = 0x00;
	/* Enable wavegen mode singleslope and enable cmp channels for PE0, PE1, PE2 */
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP2EN_bm;;
	/* Set PWM period and position */
	TCA0.SINGLE.PER = per;
	
	/* Set pulse p for LED0-2 */
	led_set_p(p);
	/* Set prescaler and enable TCA0 */
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc | TCA_SINGLE_ENABLE_bm;
}

/* DIM DIM DIM  */
void led_set_p(uint16_t p){
	TCA0.SINGLE.CMP0BUF = p;
	TCA0.SINGLE.CMP1BUF = p;
	TCA0.SINGLE.CMP2BUF = p;
}

/* sel = 0 for LED0-2, sel = 1 for [P4, P5, P6] */
void pmux_out(uint8_t sel){
	switch (sel){
		case 0:
			PORTMUX.TCAROUTEA |= PORTMUX_TCA0_PORTC_gc;
			break;
		case 1:
			PORTMUX.TCAROUTEA |= PORTMUX_TCA0_PORTE_gc;
			break;
		default:
			break;
	}
}


/* Takes an integer input which corresponds to a P4(0), P5(1), P6(2) */
void init_pwm_selector(uint16_t p, uint8_t selector){
	/* Set sel as output, invert */
	PORTE.DIR |= (1 << selector);

	switch (selector){
		case 0:
			TCA0.SINGLE.CMP0BUF = p;
			PORTE.PIN0CTRL |= PORT_INVEN_bm;
			TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
			break;
		case 1:
			TCA0.SINGLE.CMP1BUF = p;
			PORTE.PIN1CTRL |= PORT_INVEN_bm;
			TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm;
			break;
		case 2:
			TCA0.SINGLE.CMP2BUF = p;
			PORTE.PIN2CTRL |= PORT_INVEN_bm;
			TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP2EN_bm;
			break;
		default:
			break;
	}
}

/* Init for supporting servos on PE0-PE2 */
void init_pwm_tri(uint16_t per, uint16_t p, uint8_t selector){
	/* Set PORTMUX to PORTE */
	PORTMUX.TCAROUTEA |= PORTMUX_TCA0_PORTE_gc;

	/* Disable TCA0 before configuring */
    TCA0.SINGLE.CTRLA = 0x00;

	/* Set PWM period */
	TCA0.SINGLE.PER = per;
	/* Set period p for selected port, and activate given port */
	init_pwm_selector(p, selector);

	/* Set prescaler and enable TCA0 */
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc | TCA_SINGLE_ENABLE_bm;

}


void button_angles(uint8_t output){

	/* Enables buttons/pullup */
	PORTD.DIRCLR = (1 << 0) | (1 << 1) | (1 << 2);
    PORTD.PIN0CTRL |= PORT_PULLUPEN_bm;
    PORTD.PIN1CTRL |= PORT_PULLUPEN_bm;
    PORTD.PIN2CTRL |= PORT_PULLUPEN_bm;
	
	uint16_t angle_out = 60;
	
	/* Each button can add 60 degrees to servo output */
	while (1){
        uint8_t sw1 = !(PORTD.IN & (1 << 0));
        uint8_t sw2 = !(PORTD.IN & (1 << 1));
        uint8_t sw3 = !(PORTD.IN & (1 << 2));
		

        if (sw1){
			servo_ctrl(output, angle_out)
            _delay_ms(15); // Debounce delay
            while (switch1){
                switch1 = !(PORTD.IN & (1 << 0));
            }
        }
        if (sw2){
			servo_ctrl(output, angle_out)
            _delay_ms(15); // Debounce delay
            while (switch2){ 
                switch2 = !(PORTD.IN & (1 << 1));
            }
        }
        if (sw3){
			servo_ctrl(output, angle_out)
            _delay_ms(15); // Debounce delay
            while (switch3){
                switch3 = !(PORTD.IN & (1 << 2));
            }
        }
		_delay_ms(10);
	}
}


/* Task 8d */
uint16_t map_angle(uint8_t angle){
	if(angle > 180){
		/* Incase angle should exceed max degrees */
		angle = 180;
	}
	/* Map value to area of motion */
	uint32_t mapval = 500 + ((uint32_t)angle * 500);
	return mapval / 180;
}
void servo_ctrl(uint8_t output, uint8_t angle){
	/* Convert angle to PWM cmp value */
	
	
	

	uint16_t cmp_val = map_angle(angle);
    init_pwm_selector(cmp_value, output);
}



/* Task 8e */
uint8_t adc_to_angle(uint16_t adc_val){
	/* [0, 4095](?), page 504 datasheet */
	/* [0, 4095] => [0, 180]deg, [-2048, 2047] => [-90, 90]deg(?)  */
    if(adc_val > 4095){
        adc_val = 4095;
    }
    uint8_t angle = (uint8_t)((adc_value * 180) / 4095);
    return angle;
}


