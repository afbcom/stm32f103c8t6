
/** \file
  \brief Pin definitions supervisor.

  Here we map to the pin definition file of the architecture at hand and also
  do some fundamental platform related stuff.
*/

#ifndef	_ARDUINO_H
#define	_ARDUINO_H


/**
  Only AVRs have a Harvard Architecture, which has distinct address spaces
  for RAM, Flash and EEPROM. All other supported targets have a single address
  space, so all the macros PROGMEM, PSTR() & co. are obsolete. Define them to
  do nothing.

  For the AVR definitions, see /usr/lib/avr/include/avr/pgmspace.h on Linux.

  With GCC 4.7 we can replace any pgm_read_* with vanilla C. Instead of PROGMEM
  we use the __flash keyword. The compiler can check anything and we can't miss
  any pgm_read_* anymore.

  Use XSTR like PSTR in PROGMEM-context.
*/
#ifndef __AVR__
  #define __flash
#endif /* ! __AVR__ */

#define FSTR(X) ((const __flash char[]) { X })
#define XSTR(X) ({static const __flash char __s[] = X; &__s[0];})

/*
	ports and functions

	added as necessary or if I feel like it- not a comprehensive list!
*/
#if defined __AVR__

  // avr/io.h is mainly for pinnames PA1 etc.
  #include <avr/io.h>

#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || \
    defined (__AVR_ATmega328P__)
	#include	"arduino_168_328p.h"
#endif

#if defined (__AVR_ATmega644__) || defined (__AVR_ATmega644P__) || \
    defined (__AVR_ATmega644PA__) || defined (__AVR_ATmega1284__) || \
    defined (__AVR_ATmega1284P__)
	#include	"arduino_644.h"
#endif

#if defined (__AVR_ATmega1280__) || defined (__AVR_ATmega2560__)
	#include	"arduino_1280.h"
#endif

#if defined (__AVR_AT90USB1286__)
  #include "arduino_usb1286.h"
#endif

#if defined (__AVR_AT90USB1287__)
  #include "arduino_usb1287.h"
#endif

#if defined (__AVR_ATmega32U4__)
	#include    "arduino_32U4.h"
#endif

#elif defined __ARMEL__

  #if defined (__ARM_LPC1114__)
    #include "arduino_lpc1114.h"
  #endif

#endif /* __AVR__, __ARMEL__, SIMULATOR */

#ifndef SIMULATOR
  #if ! defined DIO0_PIN && ! defined PIO0_1_PIN
    #error Pins for this chip not defined in arduino.h! If you write an \
           appropriate pin definition and have this firmware work on your chip, \
           please tell us via Github or the forum thread.
  #endif
#endif

#ifndef BSS
  #define BSS __attribute__ ((__section__ (".bss")))
#endif

#endif /* _ARDUINO_H */
