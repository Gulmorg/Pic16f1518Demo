/*
 * File:   pwm.h
 * Author: Utku
 *
 * Created on December 15, 2022, 9:27 AM
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_MAX_DUTY 1023

double _pwmFreq = 0;

void pwm_set_freq(double freq) {
    PR2 = (unsigned char) ((_XTAL_FREQ / (freq * 4 * TMR2PRESCALE)) - 1);
    _pwmFreq = freq;
}

unsigned int pwm_calculate_duty(double duty) {
    return (unsigned int) (((duty / PWM_MAX_DUTY) * (1 / _pwmFreq)) / ((1 / (double) _XTAL_FREQ) * TMR2PRESCALE));
}

#endif
