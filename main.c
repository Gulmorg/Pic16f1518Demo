// Interrupt every 1ms
#define TMR0PRESCALE 16
#define TMR0RESET 6

#define TMR2PRESCALE 64

#define _XTAL_FREQ 16000000

// Max Brightness = 1023
#define LED_BRIGHTNESS 500
// Max volume = `((Max Duty + 1) / 2) - 1 = `511´ or just = `Max Duty / 2 = `511´ since the carry bit is discarded*/
#define BUZZER_VOLUME 0
// Configuration
#include "config.h"
#include <xc.h>

// Variables
unsigned int _ledCounter = 0;
unsigned char _toneMode = 0;
unsigned char _buzzerRepeatCount = 0;

__bit _ledEnabled = 0;
__bit _buzzerEnabled = 0;
__bit _ledSpeedFast = 0;
__bit _ledOn = 0;
unsigned int _lbTemp = 0;

// Modules
#include "modules.h"

// Pins
#include "pins.h"

void __interrupt() led_isr() {
    if (INTCONbits.T0IF) {
        tmr0_reset();
        wdt_clear();

        if (_buzzerEnabled) {
            // '1 = 000' '2 = 001' '3 = 010' '4 = 011' '5 = 100' '6 = 101' '7 = 110' '8 = 111'
            switch (_toneMode) {
                case 1: toneMode1();
                    break;
                case 2: toneMode2();
                    break;
                case 3: toneMode3();
                    break;
                case 4: toneMode4();
                    break;
                case 5: toneMode5();
                    break;
                case 6: toneMode6();
                    break;
                case 7: toneMode7();
                    break;
                case 8: toneMode8();
                    break;
            }
        }

        if (_ledEnabled) {
            _ledCounter++;
            if (_ledSpeedFast) { // 1Hz
                if (_ledOn && _ledCounter >= 175) {
                    _ledOn = 0;
                    _ledCounter = 0;
                    pwm2_disable();
                    RC1 = 0;
                } else if (!_ledOn && _ledCounter >= 825) {
                    pwm2_set_duty(_lbTemp);
                    _lbTemp += 100;
                    if (_lbTemp == 1000) _lbTemp = 0;
                    pwm2_enable();
                    _ledOn = 1;
                    _ledCounter = 0;
                }
            } else { // 0.5Hz
                if (_ledOn && _ledCounter >= 175) {
                    _ledOn = 0;
                    _ledCounter = 0;
                    pwm2_disable();
                    RC1 = 0;
                } else if (!_ledOn && _ledCounter >= 1640) {
                    pwm2_set_duty(_lbTemp);
                    _lbTemp += 100;
                    if (_lbTemp == 1000) _lbTemp = 0;
                    pwm2_enable();
                    _ledOn = 1;
                    _ledCounter = 0;
                }
            }
        }
    }
}

void main(void) {
    intosc_set_freq();

    wdt_init(WDT_1S);
    wdt_enable();

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

    tmr0_init();
    tmr2_init();

    __delay_ms(50);

    if (_ledEnabled) {
        // Select Flash Mode
        _ledSpeedFast = FLASH_SPEED_PIN;
        pwm2_enable();
        TRISCbits.TRISC1 = 0;
    }

    if (_buzzerEnabled) {
        // Select Tone
        _toneMode = (unsigned char) (8 - (((int) TONE_PIN_0 << 2) + ((int) TONE_PIN_1 << 1) + (int) TONE_PIN_2));
        pwm1_enable();
        TRISCbits.TRISC2 = 0;
    } else {
        PR2 = 255;
    }

    tmr0_enable();
    tmr2_enable();

    wdt_init(WDT_16MS);

    while (1);

    return;
}
