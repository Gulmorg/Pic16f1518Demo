/*
 * File:   pwm.h
 * Author: Utku
 *
 * Created on December 15, 2022, 9:27 AM
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_MAX_DUTY 1023

void pwm_set_freq(double freq) {
    PR2 = (unsigned char) ((_XTAL_FREQ / (freq * 4 * TMR2PRESCALE)) - 1);
}

unsigned int pwm_calculate_duty(double duty) {
    return (unsigned int) ((duty * 4 * (PR2 + 1)) / PWM_MAX_DUTY);
}

#endif
