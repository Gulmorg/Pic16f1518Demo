/*
 * File:   pwm2.h
 * Author: Utku
 *
 * Created on December 15, 2022, 9:26 AM
 */

#ifndef PWM2_H
#define	PWM2_H

#define pwm2_enable() CCP2CONbits.CCP2M3 = 1; CCP2CONbits.CCP2M2 = 1; TRISCbits.TRISC1 = 0
#define pwm2_disable() CCP2CONbits.CCP2M = 0

void pwm2_set_duty(unsigned int duty) {
    if (duty == 0) {
        pwm2_disable();
        RC1 = 0;
    } else if (duty == PWM_MAX_DUTY) {
        pwm2_disable();
        RC1 = 1;
    } else {
        pwm2_enable();
        duty = (unsigned int) pwm_get_duty(duty);
        if (duty == 0) duty = 1;
        CCP2CONbits.DC2B1 = duty & 2;
        CCP2CONbits.DC2B0 = duty & 1;
        CCPR2L = (unsigned char) (duty >> 2);
    }
}

#endif

