// Interrupt every 1ms
#define TMR0PRESCALE 16
#define TMR0RESET 6

#define TMR2PRESCALE 64
#define BUZZER_VOLUME 511 /* Max volume = `((Max Duty + 1) / 2) - 1 = `511´
                                or just = `Max Duty / 2 = `511´ since the carry bit is discarded */
#define _XTAL_FREQ 16000000

// Configuration
#include "config.h"
#include <xc.h>

// Variables
unsigned long _pwmFreq = 0;
unsigned int _buzzerCounter = 0;
unsigned int _ledCounter = 0;
unsigned char _toneMode = 0;
unsigned char _buzzerState = 0;

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

        if (_buzzerEnabled) {
            _buzzerCounter++;

            wdt_clear();
            int ledStateCount = 4;
            if (_buzzerState == 0) {
                pwm_set_freq(554);
                pwm1_set_duty(BUZZER_VOLUME);
                _buzzerState++;
            }
            if(_buzzerState == 1) {
                if (_buzzerCounter < 100) {
                    _buzzerCounter++;
                } else {
                    _buzzerCounter = 0;
                    _buzzerState++;
                }
            }
            if (_buzzerState == 2) {
                pwm_set_freq(440);
                pwm1_set_duty(BUZZER_VOLUME);
            }
            if (_buzzerState == 3) {
                if (_buzzerCounter < 400) {
                    _buzzerCounter++;
                } else {
                    _buzzerCounter = 0;
                    _buzzerState++;
                }
            }
            if (_buzzerState == ledStateCount) _buzzerState = 0;
        }

        if (_ledEnabled) {
            wdt_clear();

            // PWM_TEST
            if (_ledFilling) _ledCounter++;
            else _ledCounter--;

            pwm2_set_duty(_ledCounter);

            if (_ledCounter == 0) _ledFilling = 1;
            else if (_ledCounter == PWM_MAX_DUTY) _ledFilling = 0;
            // PWM_TEST_END

            //                        _ledCounter++;
            //                        if (_ledSpeedFast) { // 1Hz
            //                            if (RC1 == 1 && _ledCounter >= 175) {
            //                                RC1 = 0;
            //                                _ledCounter = 0;
            //                            } else if (RC1 == 0 && _ledCounter >= 825) {
            //                                RC1 = 1;
            //                                _ledCounter = 0;
            //                            }
            //                        } else { // 0.5Hz
            //                            if (RC1 == 1 && _ledCounter >= 175) {
            //                                RC1 = 0;
            //                                _ledCounter = 0;
            //                            } else if (RC1 == 0 && _ledCounter >= 1640) {
            //                                RC1 = 1;
            //                                _ledCounter = 0;
            //                            }
            //                        }
        }
    }
}

void main(void) {
    wdt_init(WDT_8S);
    wdt_enable();

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
        // Select Tone (3, 4, 6, 7, 8)
        _toneMode = (unsigned char) (8 - (((int) TONE_PIN_0 << 2) + ((int) TONE_PIN_1 << 1) + (int) TONE_PIN_2));
        pwm1_enable();
        TRISCbits.TRISC2 = 0;
    }

    // PWM_TEST
    _toneMode = 3;
    _ledFilling = 1;
    // PWM_TEST_END

    tmr0_enable();
    tmr2_enable();

    while (1);

    return;
}
