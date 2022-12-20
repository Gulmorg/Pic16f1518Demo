/*
 * File:   wdt.h
 * Author: Utku
 *
 * Created on December 16, 2022, 12:02 PM
 */

#ifndef WDT_H
#define	WDT_H

// Prescaler values
#define WDT_1MS 0b0
#define WDT_2MS 0b1
#define WDT_4MS 0b10
#define WDT_8MS 0b11
#define WDT_16MS 0b100
#define WDT_32MS 0b101
#define WDT_64MS 0b110
#define WDT_128MS 0b111
#define WDT_256MS 0b1000
#define WDT_512MS 0b1001
#define WDT_1S 0b1010
#define WDT_2S 0b1011
#define WDT_4S 0b1100
#define WDT_8S 0b1101
#define WDT_16S 0b1110
#define WDT_32S 0b1111
#define WDT_64S 0b10000
#define WDT_128S 0b10001
#define WDT_256S 0b10010

#define wdt_init(prescaler) WDTCONbits.WDTPS = prescaler

#define wdt_enable() WDTCONbits.SWDTEN = 1
#define wdt_disable() WDTCONbits.SWDTEN = 0

void wdt_clear() {
    __asm("clrwdt");
}

#endif

