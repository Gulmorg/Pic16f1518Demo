/*
 * File:   oscillator.h
 * Author: Utku
 *
 * Created on December 16, 2022, 11:27 AM
 */

#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

void intosc_set_freq(void) {
#if _XTAL_FREQ == 16000000
    OSCCONbits.IRCF = 0b1111;
#elif _XTAL_FREQ == 8000000
    OSCCONbits.IRCF = 0b1110;
#elif _XTAL_FREQ == 4000000
    OSCCONbits.IRCF = 0b1101;
#elif _XTAL_FREQ == 2000000
    OSCCONbits.IRCF = 0b1100;
#elif _XTAL_FREQ == 1000000
    OSCCONbits.IRCF = 0b1011;
#elif _XTAL_FREQ == 500000
    OSCCONbits.IRCF = 0b0111;
#elif _XTAL_FREQ == 250000
    OSCCONbits.IRCF = 0b0110;
#elif _XTAL_FREQ == 125000
    OSCCONbits.IRCF = 0b0101;
#elif _XTAL_FREQ == 62500
    OSCCONbits.IRCF = 0b0100;
#elif _XTAL_FREQ == 31250
    OSCCONbits.IRCF = 0b0010;
#elif _XTAL_FREQ == 31000
    OSCCONbits.IRCF = 0b0001;
#else
#error Invalid Oscillator Frequency (_XTAL_FREQ)
#endif
}

#endif

