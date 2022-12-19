/*
 * File:   wdt.h
 * Author: Utku
 *
 * Created on December 16, 2022, 12:02 PM
 */

#ifndef WDT_H
#define	WDT_H

// Prescaler values
#define WDT_8S 0b01101

#define wdt_init(prescaler) WDTCONbits.WDTPS = prescaler

#define wdt_enable() WDTCONbits.SWDTEN = 1
#define wdt_disable() WDTCONbits.SWDTEN = 0

void wdt_clear() { __asm("clrwdt"); }

#endif

