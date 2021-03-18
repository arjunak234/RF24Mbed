
/*
 Copyright (C)
    2011            J. Coliz <maniacbug@ymail.com>
    2015-2019 TMRh20
    2015            spaniakos <spaniakos@gmail.com>
    2015            nerdralph
    2015            zador-blood-stained
    2016            akatran
    2017-2019 Avamander <avamander@gmail.com>
    2019            IkpeohaGodson

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
*/

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

/*** USER DEFINES:    ***/
#define FAILURE_HANDLING
//#define SERIAL_DEBUG
//#define MINIMAL

/**
 * User access to internally used delay time (in microseconds) during RF24::powerUp()
 * @warning This default value compensates for all supported hardware. Only adjust this if you
 * know your radio's hardware is, in fact, genuine and reliable.
 */
#if !defined(RF24_POWERUP_DELAY)
#define RF24_POWERUP_DELAY 5000
#endif

/**********************/
#define rf24_max(a, b) (a > b ? a : b)
#define rf24_min(a, b) (a < b ? a : b)

#define RF24_SPI_SPEED 10000000
#define _BV(x) (1 << (x))
#define PSTR(x) (x)
#define PRIPSTR "%s"
#define pgm_read_word(p) (*(p))
#define pgm_read_byte(p) (*(p))
#define pgm_read_ptr(p) (*(p))

#define HIGH true
#define LOW false

#ifdef SERIAL_DEBUG
#define IF_SERIAL_DEBUG(x) ({ x; })
#else
#define IF_SERIAL_DEBUG(x)
#endif

#endif // __RF24_CONFIG_H__
