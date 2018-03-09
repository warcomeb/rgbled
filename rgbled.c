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

#include "rgbled.h"

RgbLed_Errors RgbLed_init (RgbLed_Device* dev)
{
    uint16_t duty = 0;
    dev->timerInit = FALSE;

    // Set to OFF all leds
    duty = (dev->type == RGBLEDTYPE_KATODE_COMMON) ? 0 : 32768;

    if (Ftm_addPwmPin(dev->timerDevice,dev->redPin,duty) == ERRORS_FTM_DEVICE_NOT_INIT)
        return RGBLEDERRORS_TIMER_NOT_INIT;

    if (Ftm_addPwmPin(dev->timerDevice,dev->greenPin,duty) == ERRORS_FTM_DEVICE_NOT_INIT)
        return RGBLEDERRORS_TIMER_NOT_INIT;

    if (Ftm_addPwmPin(dev->timerDevice,dev->bluePin,duty) == ERRORS_FTM_DEVICE_NOT_INIT)
        return RGBLEDERRORS_TIMER_NOT_INIT;

    dev->timerInit = TRUE;
    return RGBLEDERRORS_OK;
}

RgbLed_Errors RgbLed_setColor (RgbLed_Device* dev,
                               uint8_t red,
                               uint8_t green,
                               uint8_t blue)
{
    if ((red > 100) || (green > 100) || (blue > 100))
        return RGBLEDERRORS_WRONG_VALUE;

    // Change value when the led is common anode
    if (dev->type == RGBLEDTYPE_ANODE_COMMON)
    {
        red = 100 - red;
        green = 100 - green;
        blue = 100 - blue;
    }

    uint16_t redDuty = (uint16_t) (((uint32_t) 32768 * red) / 100);
    uint16_t greenDuty = (uint16_t) (((uint32_t) 32768 * green) / 100);
    uint16_t blueDuty = (uint16_t) (((uint32_t) 32768 * blue) / 100);

    if (dev->timerInit == FALSE) return RGBLEDERRORS_TIMER_NOT_INIT;

    Ftm_setPwm(dev->timerDevice,dev->redChannel,redDuty);
    Ftm_setPwm(dev->timerDevice,dev->greenChannel,greenDuty);
    Ftm_setPwm(dev->timerDevice,dev->blueChannel,blueDuty);

    return RGBLEDERRORS_OK;
}

#if (WARCOMEB_RGBLED_DEBUG == 1)

/**************************** CLI Section *************************************/

/**
 * TODO
 */
static void RgbLed_cliHelp()
{
    Cli_sendHelpString("help","Print help information");
    Cli_sendHelpString("color <R> <G> <B>","Set color with value between 0-100");
}

void RgbLed_cliParser(void* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE])
{
    if ((argc == 1) || ((argc == 2) && (strcmp(argv[1],"help") == 0)))
    {
        RgbLed_cliHelp();
        return;
    }

    if ((argc == 5) && (strcmp(argv[1],"color") == 0))
    {
        uint8_t red = 0, green = 0, blue = 0;
        System_Errors errorRed, errorGreen, errorBlue;
        RgbLed_Errors error;

        errorRed = dtu8(argv[2],&red,strlen(argv[2]));
        errorGreen = dtu8(argv[3],&green,strlen(argv[3]));
        errorBlue = dtu8(argv[4],&blue,strlen(argv[4]));

        if ((errorRed != ERRORS_UTILITY_CONVERSION_OK)   ||
            (errorGreen != ERRORS_UTILITY_CONVERSION_OK) ||
            (errorBlue != ERRORS_UTILITY_CONVERSION_OK))
        {
            LOCCIONI_CLI_WRONGPARAM();
            return;
        }

        error = RgbLed_setColor(dev,red,green,blue);
        if (error != RGBLEDERRORS_OK)
        {
            LOCCIONI_CLI_WRONGPARAM();
            return;
        }

        LOCCIONI_CLI_DONECMD();
        return;
    }

    LOCCIONI_CLI_WRONGCMD();
}

#endif
