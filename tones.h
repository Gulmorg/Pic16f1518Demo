/*
 * File:   tones.h
 * Author: Utku
 *
 * Created on December 16, 2022, 10:37 AM
 */

#ifndef TONES_H
#define	TONES_H

unsigned int _buzzerCounter = 0;

void toneMode1(void) { // NEN 2575 500Hz-1200Hz,3.5s, OFF 0.5s
    while (1) {
        wdt_clear();
        unsigned char period = 124; // 500 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        for (int i = 0; i < 74; i++) // 124 ile 50 arasinda 74 aralik var
        {
            PR2 = period;
            _buzzerCounter = 0;
            while (_buzzerCounter < 47);
            period--;
        }
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 500);
    }
}

void toneMode2(void) { // AS1670 Evacuation 1000-2500Hz 0,5s-0,5s off x 3 / 1,5s off
    while (1) {
        wdt_clear();
        unsigned char period = 62; //  1000 Hz
        for (int a = 0; a < 3; a++) // 3 tekrar için
        {
            pwm1_set_duty(BUZZER_VOLUME);
            for (int i = 0; i < 37; i++) // for (int i=249>99;i--)   62 den 25e kadar azaltarak 1Khz den 2.5 Khz e kadar yükseltildi.
            {
                PR2 = period;
                _buzzerCounter = 0;
                while (_buzzerCounter < 14);
                period--;
            }
            period = 62;
            pwm1_set_duty(0);
            _buzzerCounter = 0;
            while (_buzzerCounter < 500);
        }
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 1000);
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

void toneMode4(void) { // ISO 8201
    switch (_buzzerState) {
        case 0:
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
            pwm1_set_duty(0);
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
    while (1) {
        wdt_clear();
        unsigned char period = 50;
        pwm1_set_duty(BUZZER_VOLUME);

        for (int i = 0; i < 74; i++) { // for (int i=249; i>99;i--)
            PR2 = period;
            _buzzerCounter = 0;
            while (_buzzerCounter < 14);
            period++;
        }
    }
}

void toneMode6(void) { // Australia AS1670 Alert Tone
    switch (_buzzerState) {
        case 0:
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
            pwm1_set_duty(0);
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
    while (1) {
        wdt_clear();
        pwm_set_freq(660); // 660 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 150);
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 150);
    }
    switch (_buzzerState) {
        case 0:
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
            pwm1_set_duty(0);
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

