/*
 * File:   pwm.h
 * Author: Utku
 *
 * Created on December 15, 2022, 9:27 AM
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_MAX_DUTY 1023

void pwm_set_freq(unsigned long freq) {
    PR2 = (unsigned char) ((_XTAL_FREQ / (freq * 4 * TMR2PRESCALE)) - 1);
    _pwmFreq = freq;
}

#define pwm_calculate_duty(duty) ((unsigned int) ((((double) duty / PWM_MAX_DUTY) * (1 / (double) _pwmFreq)) / ((1 / (double) _XTAL_FREQ) * TMR2PRESCALE)))

#endif
