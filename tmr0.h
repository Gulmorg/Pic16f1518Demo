/*
 * File:   tmr0.h
 * Author: Utku Do?anay
 *
 * Created on December 2, 2022, 9:32 AM
 */

#ifndef TMR0_H
#define TMR0_H

void tmr0_init(void) {
    // Checck if defines are present and valid
#ifndef TMR0PRESCALE
#error TMR0PRESCALE needs to be defined
#endif
#if (TMR0PRESCALE != 1 && TMR0PRESCALE != 2 && TMR0PRESCALE != 4 && TMR0PRESCALE != 8 && TMR0PRESCALE != 16 && TMR0PRESCALE != 32 && TMR0PRESCALE != 64 && TMR0PRESCALE != 128 && TMR0PRESCALE != 256)
#error TMR0PRESCALE can only take values 1, 2, 4, 8, 16, 32, 64, 128, and 256
#endif
#ifdef TMR0RESET
#if (TMR0RESET > 255 || TMR0RESET < 0)
#error TMR0RESET can only take values 0 through 255
#endif
#else
#define TMR0RESET 0
#endif

    // Set Timer0 Prescaler
#if TMR0PRESCALE == 1
    OPTION_REGbits.PSA = 1;
#else
    OPTION_REGbits.PSA = 0;
#if TMR0PRESCALE == 2
    OPTION_REGbits.PS = 0b000;
#elif TMR0PRESCALE == 4
    OPTION_REGbits.PS = 0b001;
#elif TMR0PRESCALE == 8
    OPTION_REGbits.PS = 0b010;
#elif TMR0PRESCALE == 16
    OPTION_REGbits.PS = 0b011;
#elif TMR0PRESCALE == 32
    OPTION_REGbits.PS = 0b100;
#elif TMR0PRESCALE == 64
    OPTION_REGbits.PS = 0b101;
#elif TMR0PRESCALE == 128
    OPTION_REGbits.PS = 0b110;
#elif TMR0PRESCALE == 256
    OPTION_REGbits.PS = 0b111;
#endif
#endif

    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.T0CS = 0;
}

#define tmr0_enable() INTCONbits.GIE = 1; INTCONbits.T0IE = 1; INTCONbits.T0IF = 0; TMR0 = TMR0RESET
#define tmr0_disable() INTCONbits.T0IE = 0
#define tmr0_reset() INTCONbits.T0IF = 0; TMR0 = TMR0RESET


#endif
