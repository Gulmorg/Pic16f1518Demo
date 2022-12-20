/*
 * File:   pwm1.h
 * Author: Utku
 *
 * Created on December 1, 2022, 11:18 AM
 */

#ifndef PWM1_H
#define PWM1_H

#define pwm1_enable() CCP1CONbits.CCP1M3 = 1; CCP1CONbits.CCP1M2 = 1
#define pwm1_disable() CCP1CONbits.CCP1M = 0

void pwm1_set_duty(unsigned int duty) {
    duty = pwm_calculate_duty(duty);
    if (duty == 0) duty = 1;
    CCP1CONbits.DC1B1 = duty & 2;
    CCP1CONbits.DC1B0 = duty & 1;
    CCPR1L = (unsigned char) (duty >> 2);
}

#endif
