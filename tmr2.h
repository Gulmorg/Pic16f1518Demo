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

#if TMR2POSTSCALE == 1
    T2CONbits.T2OUTPS = 0b0000;
#elif TMR2POSTSCALE == 2
    T2CONbits.T2OUTPS = 0b0001;
#elif TMR2POSTSCALE == 3
    T2CONbits.T2OUTPS = 0b0010;
#elif TMR2POSTSCALE == 4
    T2CONbits.T2OUTPS = 0b0011;
#elif TMR2POSTSCALE == 5
    T2CONbits.T2OUTPS = 0b0100;
#elif TMR2POSTSCALE == 6
    T2CONbits.T2OUTPS = 0b0101;
#elif TMR2POSTSCALE == 7
    T2CONbits.T2OUTPS = 0b0110;
#elif TMR2POSTSCALE == 8
    T2CONbits.T2OUTPS = 0b0111;
#elif TMR2POSTSCALE == 9
    T2CONbits.T2OUTPS = 0b1000;
#elif TMR2POSTSCALE == 10
    T2CONbits.T2OUTPS = 0b1001;
#elif TMR2POSTSCALE == 11
    T2CONbits.T2OUTPS = 0b1010;
#elif TMR2POSTSCALE == 12
    T2CONbits.T2OUTPS = 0b1011;
#elif TMR2POSTSCALE == 13
    T2CONbits.T2OUTPS = 0b1100;
#elif TMR2POSTSCALE == 14
    T2CONbits.T2OUTPS = 0b1101;
#elif TMR2POSTSCALE == 15
    T2CONbits.T2OUTPS = 0b1110;
#elif TMR2POSTSCALE == 16
    T2CONbits.T2OUTPS = 0b1111;
#endif
}

#define tmr2_enable() T2CONbits.TMR2ON = 1; TMR2 = 0
#define tmr2_disable() T2CONbits.TMR2ON = 0;

#endif
