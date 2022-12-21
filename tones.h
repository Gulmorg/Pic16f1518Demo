/*
 * File:   tones.h
 * Author: Utku
 *
 * Created on December 16, 2022, 10:37 AM
 */

#ifndef TONES_H
#define	TONES_H

#define TONE_1_START_FREQ 500
#define TONE_1_END_FREQ 1200
#define TONE_2_START_FREQ 1000
#define TONE_2_END_FREQ 2500
#define TONE_5_START_FREQ 1200
#define TONE_5_END_FREQ 500

double _tone1Freq = TONE_1_START_FREQ;
double _tone2Freq = TONE_2_START_FREQ;
double _tone5Freq = TONE_5_START_FREQ;
unsigned int _buzzerCounter = 0;
unsigned char _buzzerState = 0;

void toneMode1(void) { // NEN 2575 500Hz-1200Hz,3.5s, OFF 0.5s
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            pwm_set_freq(_tone1Freq);
            pwm1_set_duty(BUZZER_VOLUME);
            _tone1Freq += 0.2; // +700Hz in 3500ms = +0.2Hz in 1ms

            if (_tone1Freq >= TONE_1_END_FREQ) {
                pwm1_disable();
                _tone1Freq = TONE_1_START_FREQ;
                _buzzerState = 1;
            }
            break;
        case 1:
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
            pwm_set_freq(_tone2Freq);
            pwm1_set_duty(BUZZER_VOLUME);
            _tone2Freq += 3; // +1500Hz in 500ms = +3Hz in 1ms

            if (_tone2Freq >= TONE_2_END_FREQ) {
                pwm1_disable();
                _tone2Freq = TONE_2_START_FREQ;
                _buzzerState = 1;
            }
            break;
        case 1:
            if (_buzzerCounter < 500) {
                _buzzerCounter++;
            } else {
                _buzzerCounter = 0;
                if (_buzzerRepeatCount < 3) {
                    _buzzerState = 0;
                    _buzzerRepeatCount++;
                } else {
                    _buzzerState = 2;
                    _buzzerRepeatCount = 0;
                }
            }
            break;
        case 2:
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
            pwm1_set_duty(BUZZER_VOLUME);
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
            pwm1_set_duty(BUZZER_VOLUME);
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
            pwm1_set_duty(BUZZER_VOLUME);
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
                if (_buzzerRepeatCount < 3) {
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

void toneMode5(void) { // DIN 33404-3
    // 1200Hz > 500Hz 1000ms
    switch (_buzzerState) {
        case 0:
            pwm_set_freq(_tone5Freq);
            pwm1_set_duty(BUZZER_VOLUME);
            _tone5Freq -= 0.7; // -700Hz in 1000ms = -0.7Hz in 1ms

            if (_tone5Freq <= TONE_5_END_FREQ) {
                _tone5Freq = TONE_5_START_FREQ;
            }
            break;
    }
}

void toneMode6(void) { // Australia AS1670 Alert Tone
    switch (_buzzerState) {
        case 0:
            pwm1_enable();
            pwm_set_freq(420);
            pwm1_set_duty(BUZZER_VOLUME);
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
            pwm1_set_duty(BUZZER_VOLUME);
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
            pwm1_set_duty(BUZZER_VOLUME);
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
            pwm_set_freq(100);
            pwm1_set_duty(BUZZER_VOLUME);
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
