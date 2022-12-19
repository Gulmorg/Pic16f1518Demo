// Interrupt every 1ms
#define TMR0PRESCALE 16
#define TMR0RESET 6

#define TMR2PRESCALE 64
#define BUZZER_VOLUME 511 // Max volume at half of max duty (511)

#define _XTAL_FREQ 16000000

// Configuration
#include "config.h"
#include <xc.h>

// Variables
unsigned long _pwmFreq = 0;
unsigned int _buzzerCounter = 0;
unsigned int _ledCounter = 0;
unsigned char _toneMode = 0;
__bit _ledEnabled = 0;
__bit _buzzerEnabled = 0;
__bit _ledSpeedFast = 0;
__bit _ledFilling = 0; // remove

// Modules
#include "modules.h"

// Pins
#include "pins.h"

void __interrupt() led_isr() {
    if (INTCONbits.T0IF) {
        tmr0_reset();

        if (_buzzerEnabled) _buzzerCounter++;

        if (_ledEnabled) {
            wdt_clear();

            //remove
            if (_ledFilling) _ledCounter++;
            else _ledCounter--;

            pwm2_set_duty(_ledCounter);

            if (_ledCounter == 0) _ledFilling = 1;
            else if (_ledCounter == PWM_MAX_DUTY) _ledFilling = 0;
            // remove

            //            _ledCounter++;
            //            if (_ledSpeedFast) { // 1Hz
            //                if (LED == 1 && _ledCounter >= 175) {
            //                    LED = 0;
            //                    _ledCounter = 0;
            //                } else if (LED == 0 && _ledCounter >= 825) {
            //                    LED = 1;
            //                    _ledCounter = 0;
            //                }
            //            } else { // 0.5Hz
            //                if (LED == 1 && _ledCounter >= 175) {
            //                    LED = 0;
            //                    _ledCounter = 0;
            //                } else if (LED == 0 && _ledCounter >= 1640) {
            //                    LED = 1;
            //                    _ledCounter = 0;
            //                }
            //            }
        }
    }
}

void main(void) {
    wdt_init(WDT_8S);
    wdt_enable();

    _ledFilling = 1; // remove

    intosc_set_freq();

    // Analog unit and analog ports are off
    ADCON0bits.ADON = 0;
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;

    // Set input/output pins
    TRISB = 0xFF;

    // Select Device Mode (Led and/or Buzzer enabled)
    if (LED_ENABLE_PIN == BUZZER_ENABLE_PIN) {
        _ledEnabled = 1;
        _buzzerEnabled = 1;
    } else {
        _ledEnabled = ~LED_ENABLE_PIN;
        _buzzerEnabled = ~BUZZER_ENABLE_PIN;
    }

    __delay_ms(50);

    tmr2_init();
    tmr2_enable();

    if (_ledEnabled) {
        // Select Flash Mode
        _ledSpeedFast = FLASH_SPEED_PIN;
        pwm2_enable();
    }

    if (_buzzerEnabled) {
        // Select Tone (3, 4, 6, 7, 8)
        _toneMode = (unsigned char) (8 - (((int) TONE_PIN_0 << 2) + ((int) TONE_PIN_1 << 1) + (int) TONE_PIN_2));
        pwm1_enable();
    }
    TRISA = 0;
    PORTA = _toneMode;
    tmr0_init();
    tmr0_enable();

    switch (_toneMode) {
        case 1: toneMode1();
        case 2: toneMode2();
        case 3: toneMode3();
        case 4: toneMode4();
        case 5: toneMode5();
        case 6: toneMode6();
        case 7: toneMode7();
        case 8: toneMode8();
        default: while (1);
    }

    return;
}
