/*
 * File:   tones.h
 * Author: Utku
 *
 * Created on December 16, 2022, 10:37 AM
 */

#ifndef TONES_H
#define	TONES_H

void toneMode1(void) {
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

void toneMode2(void) {
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

void toneMode3(void) {
    while (1) {
        wdt_clear();
        PR2 = 111; // 554 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 100);
        PR2 =  142; //  440 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 400);
    }
}

void toneMode4(void) {
    while (1) {
        wdt_clear();
        for (unsigned char i = 0; i < 3; i++) { // 3 tekrar için
            PR2 = 25; // 2500 Hz
            pwm1_set_duty(BUZZER_VOLUME);
            _buzzerCounter = 0;
            while (_buzzerCounter < 500);
            pwm1_set_duty(0);
            _buzzerCounter = 0;
            while (_buzzerCounter < 500);
        }
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 1000);
    }
}

void toneMode5(void) {
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

void toneMode6(void) {
    while (1) {
        wdt_clear();
        PR2 = 148; //420 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 600);
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 600);
    }
}

void toneMode7(void) {
    while (1) {
        wdt_clear();
        PR2 = 95; // 660 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 150);
        pwm1_set_duty(0);
        _buzzerCounter = 0;
        while (_buzzerCounter < 150);
    }
}

void toneMode8(void) {
    while (1) {
        wdt_clear();
        PR2 = 76; // 800 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 500);
        PR2 = 62; // 1000 Hz
        pwm1_set_duty(BUZZER_VOLUME);
        _buzzerCounter = 0;
        while (_buzzerCounter < 500);
    }
}


#endif

