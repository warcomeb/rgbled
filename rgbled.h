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

/**
 * In this file you must define the...
 */
#ifndef __NO_BOARD_H
#include "board.h"
#endif

#define WARCOMEB_RGBLED_LIBRARY_VERSION     "1.0.0"
#define WARCOMEB_RGBLED_LIBRARY_VERSION_M   1
#define WARCOMEB_RGBLED_LIBRARY_VERSION_m   0
#define WARCOMEB_RGBLED_LIBRARY_VERSION_bug 0
#define WARCOMEB_RGBLED_LIBRARY_TIME        0

typedef enum
{
    RGBLEDTYPE_ANODE_COMMON,
    RGBLEDTYPE_KATODE_COMMON,
} RgbLed_Type;

typedef struct _RgbLed_Device
{
    Ftm_DeviceHandle timerDevice;

    Ftm_Pins redPin;
    Ftm_Channels redChannel;

    Ftm_Pins greenPin;
    Ftm_Channels greenChannel;

    Ftm_Pins bluePin;
    Ftm_Channels blueChannel;

    RgbLed_Type type;

    uint16_t frequency;

} RgbLed_Device;

/**
 *
 */
void RgbLed_init (RgbLed_Device* dev);

#if (WARCOMEB_RGBLED_DEBUG == 1)

void RgbLed_cliParser(void* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE]);

#endif // (WARCOMEB_RGBLED_DEBUG == 1)

#endif // __WARCOMEB_RGBLED_H
