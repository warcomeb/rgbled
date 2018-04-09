/******************************************************************************
 * RGBLED library
 * Copyright (C) 2018 Marco Giammarini
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

/******************************************************************************
 * @mainpage RGB LEDs library based on @a libohiboard
 *
 * @section changelog ChangeLog
 *
 * @li v1.0.0 of 2018/03/xx - Initial version
 *
 * @section mustdo Mondatory define
 * In this section we explain the define that the user must define.
 * @li WARCOMEB_RGBLED_TIMER this define serves to indicate if the timer is
 * used or not.
 *
 * @section library External Library
 *
 * The library use the following external library
 * @li libohiboard https://github.com/ohilab/libohiboard a C framework for
 * NXP Kinetis microcontroller
 * @li cli https://github.com/Loccioni-Electronic/cli Small library for a simple
 * command line interface based on microcontroller UART
 *
 *
 ******************************************************************************/

#ifndef __WARCOMEB_RGBLED_H
#define __WARCOMEB_RGBLED_H

#ifndef __NO_BOARD_H
#include "board.h"
#endif

#define WARCOMEB_RGBLED_LIBRARY_VERSION     "1.0.0"
#define WARCOMEB_RGBLED_LIBRARY_VERSION_M   1
#define WARCOMEB_RGBLED_LIBRARY_VERSION_m   0
#define WARCOMEB_RGBLED_LIBRARY_VERSION_bug 0
#define WARCOMEB_RGBLED_LIBRARY_TIME        0

#define WARCOMEB_RGBLED_FREQUENCY           1000 // [Hz]

#if !defined(WARCOMEB_RGBLED_TIMER)
#error "You must define a device type to manage leds!"
#endif

typedef enum
{
    RGBLEDTYPE_ANODE_COMMON,
    RGBLEDTYPE_KATODE_COMMON,
} RgbLed_Type;

typedef enum _RgbLed_Errors
{
    /**< No Errors */
    RGBLEDERRORS_OK                    = 0x00,

    RGBLEDERRORS_TIMER_NOT_INIT,
    RGBLEDERRORS_WRONG_VALUE,

} RgbLed_Errors;

/**
 *
 */
typedef struct _RgbLed_Device
{
#if (WARCOMEB_RGBLED_TIMER > 0)

    Ftm_DeviceHandle timerDevice;
    bool timerInit;

    Ftm_Pins redPin;
    Ftm_Channels redChannel;

    Ftm_Pins greenPin;
    Ftm_Channels greenChannel;

    Ftm_Pins bluePin;
    Ftm_Channels blueChannel;

#else

    Gpio_Pins redPin;
    Gpio_Pins greenPin;
    Gpio_Pins bluePin;

#endif

    RgbLed_Type type;

} RgbLed_Device;

/**
 *
 * @param dev
 * @return
 */
RgbLed_Errors RgbLed_init (RgbLed_Device* dev);

/**
 * @param dev
 * @param red
 * @param green
 * @param blue
 * @return
 */
RgbLed_Errors RgbLed_setColor (RgbLed_Device* dev,
                               uint8_t red,
                               uint8_t green,
                               uint8_t blue);

#if (WARCOMEB_RGBLED_DEBUG == 1)

#include "cli/cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RgbLed_cliParser(void* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE]);

#endif // (WARCOMEB_RGBLED_DEBUG == 1)

#endif // __WARCOMEB_RGBLED_H
