/*
 * File:   tmr2.h
 * Author: Utku
 *
 * Created on December 2, 2022, 9:36 AM
 */

#ifndef TMR2_H
#define	TMR2_H

void tmr2_init(void) {
    // Check if defines are valid
#ifdef TMR2PRESCALE
#if (TMR2PRESCALE != 1 && TMR2PRESCALE != 4 && TMR2PRESCALE != 16 && TMR2PRESCALE != 64)
#error TMR2PRESCALE can only take values 1, 4, 16, and 64
#endif
#else
#define TMR2PRESCALE 64
#endif
#ifdef TMR2POSTSCALE
#if (TMR2POSTSCALE > 16 || TMR2POSTSCALE < 1)
#error TMR2PRESCALE can only take values 1 through 16
#endif
#else
#define TMR2POSTSCALE 1
#endif

    // Set Timer2 Prescaler and Postscaler
#if TMR2PRESCALE == 1
    T2CONbits.T2CKPS = 0b00;
#elif TMR2PRESCALE == 4
    T2CONbits.T2CKPS = 0b01;
#elif TMR2PRESCALE == 16
    T2CONbits.T2CKPS = 0b10;
#elif TMR2PRESCALE == 64
    T2CONbits.T2CKPS = 0b11;
#endif

    T2CONbits.T2OUTPS = TMR2POSTSCALE - 1; // -1 Because 0b0000 is DIV_BY_1
}

#define tmr2_enable() T2CONbits.TMR2ON = 1; TMR2 = 0;
#define tmr2_disable() T2CONbits.TMR2ON = 0;

#endif
