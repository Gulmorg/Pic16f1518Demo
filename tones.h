/*
 * File:   tones.h
 * Author: Utku
 *
 * Created on December 16, 2022, 10:37 AM
 */

#ifndef TONES_H
#define	TONES_H

#define TONE_1_START_PERIOD 124
#define TONE_1_END_PERIOD 50
#define TONE_2_START_PERIOD 62
#define TONE_2_END_PERIOD 25
#define TONE_5_START_PERIOD 50
#define TONE_5_END_PERIOD 124

unsigned char _tone1Period = TONE_1_START_PERIOD;
unsigned char _tone2Period = TONE_2_START_PERIOD;
unsigned char _tone5Period = TONE_5_START_PERIOD;
unsigned char _toneCounter = 0;
unsigned int _buzzerCounter = 0;
unsigned char _buzzerState = 0;

void toneMode1(void) { // NEN 2575 500Hz-1200Hz,3.5s, OFF 0.5s
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            _buzzerState = 1;
        case 1:
            PR2 = _tone1Period;
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 2;
        case 2:
            if (_toneCounter < 46) { // Count for 47 milliseconds
                _toneCounter++;
            } else {
                _tone1Period--; // Reduce period by 1 every 47 milliseconds so it's reduced by 74 every 3500 milliseconds
                _toneCounter = 0;

                if (_tone1Period > TONE_1_END_PERIOD) {
                    _buzzerState = 1;
                } else {
                    pwm1_disable();
                    _tone1Period = TONE_1_START_PERIOD;
                    _buzzerState = 3;
                }
            }
            break;
        case 3:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode2(void) { // AS1670 Evacuation 1000-2500Hz 0,5s-0,5s off x 3 / 1,5s off
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            _buzzerState = 1;
        case 1:
            PR2 = _tone2Period;
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 2;
        case 2:
            if (_toneCounter < 13) { // Count for 14 milliseconds
                _toneCounter++;
            } else {
                _tone2Period--; // Reduce period by 1 every 14 milliseconds so it's reduced by 37 every 500 milliseconds
                _toneCounter = 0;

                if (_tone2Period > TONE_2_END_PERIOD) {
                    _buzzerState = 1;
                } else {
                    pwm1_disable();
                    _tone2Period = TONE_2_START_PERIOD;
                    _buzzerState = 3;
                }
            }
            break;
        case 3:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                if (_buzzerRepeatCount < 2) {
                    _buzzerState = 0;
                    _buzzerRepeatCount++;
                } else {
                    _buzzerState = 4;
                    _buzzerRepeatCount = 0;
                }
            }
            break;
        case 4:
            if (_buzzerCounter < 1000) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode3(void) { //!!! AFNOR NF S32-001 554 Hz 0.1s, 440 Hz 0.4s
    switch (_buzzerState) {
        case 0:
            pwm_set_freq(544);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
            break;
        case 1:
            if (_buzzerCounter < 100) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 2;
            }
            break;
        case 2:
            pwm_set_freq(440);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 3;
            break;
        case 3:
            if (_buzzerCounter < 400) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode4(void) { // ISO 8201 2500 Hz 0.5sn ON /0.5 OFFx3 /1,5 sn OFF
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            pwm_set_freq(2500);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
            break;
        case 1:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 2;
            }
            break;
        case 2:
            pwm1_disable();
            _buzzerState = 3;
            break;
        case 3:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                if (_buzzerRepeatCount < 2) {
                    _buzzerState = 0;
                    _buzzerRepeatCount++;
                } else {
                    _buzzerState = 4;
                    _buzzerRepeatCount = 0;
                }
            }
            break;
        case 4:
            if (_buzzerCounter < 1000) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode5(void) { // DIN 33404-3 1200Hz-500Hz 1000ms
    switch (_buzzerState) {
        case 0:
            PR2 = _tone5Period;
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
        case 1:
            if (_toneCounter < 13) { // Count for 14 milliseconds
                _toneCounter++;
            } else {
                _tone5Period++; // Increase period by 1 every 14 milliseconds so it's increased by 74 every 1000 milliseconds
                _toneCounter = 0;

                if (_tone5Period > TONE_5_END_PERIOD) {
                    _tone5Period = TONE_5_START_PERIOD;
                }
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode6(void) { // Australia AS1670 Alert Tone
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            pwm_set_freq(420);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
            break;
        case 1:
            if (_buzzerCounter < 600) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 2;
            }
            break;
        case 2:
            pwm1_disable();
            _buzzerState = 3;
            break;
        case 3:
            if (_buzzerCounter < 600) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode7(void) { // 660 Hz 0.15s ON , 0.15s OFF
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            pwm_set_freq(660);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
            break;
        case 1:
            if (_buzzerCounter < 150) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 2;
            }
            break;
        case 2:
            pwm1_disable();
            _buzzerState = 3;
            break;
        case 3:
            if (_buzzerCounter < 150) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

void toneMode8(void) { // 800Hz/1000Hz 0.5s each
    switch (_buzzerState) {
        case 0:
            pwm_set_freq(800);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 1;
            break;
        case 1:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 2;
            }
            break;
        case 2:
            pwm_set_freq(1000);
            pwm1_set_duty(BUZZER_VOLUME_DUTY);
            _buzzerState = 3;
            break;
        case 3:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                _buzzerState = 0;
            }
            break;
    }
}

#endif
