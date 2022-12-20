/*
 * File:   pwm2.h
 * Author: Utku
 *
 * Created on December 15, 2022, 9:26 AM
 */

#ifndef PWM2_H
#define	PWM2_H

#define pwm2_enable() CCP2CONbits.CCP2M3 = 1; CCP2CONbits.CCP2M2 = 1
#define pwm2_disable() CCP2CONbits.CCP2M = 0

void pwm2_set_duty(unsigned int duty) {
    duty = pwm_calculate_duty(duty);
    if (duty == 0) duty = 1;
    CCP2CONbits.DC2B1 = duty & 2;
    CCP2CONbits.DC2B0 = duty & 1;
    CCPR2L = (unsigned char) (duty >> 2);
}

#endif
