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

#if (WARCOMEB_RGBLED_DEBUG == 1)

/**************************** CLI Section *************************************/

/**
 * TODO
 */
static void RgbLed_cliHelp()
{
    Cli_sendHelpString("help","Print help information");
    Cli_sendHelpString("status","Print status information");
}

void RgbLed_cliParser(void* dev, int argc, char argv[][LOCCIONI_CLI_BUFFER_SIZE])
{
    if ((argc == 1) || ((argc == 2) && (strcmp(argv[1],"help") == 0)))
    {
        RgbLed_cliHelp();
        return;
    }

    LOCCIONI_CLI_WRONGCMD();
}

#endif
