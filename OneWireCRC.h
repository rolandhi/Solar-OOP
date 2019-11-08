/*
* OneWireCRC. This is a port to mbed of Jim Studt's Adruino One Wire
* library. Please see additional copyrights below this one, including
* references to other copyrights.
*
* Copyright (C) <2009> Petras Saduikis <petras@petras.co.uk>
*
* This file is part of OneWireCRC.
*
* OneWireCRC is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* OneWireCRC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with OneWireCRC.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
Copyright (c) 2007, Jim Studt

Updated to work with arduino-0008 and to include skip() as of
2007/07/06. --RJL20

Modified to calculate the 8-bit CRC directly, avoiding the need for
the 256-byte lookup table to be loaded in RAM.  Tested in arduino-0010
-- Tom Pollard, Jan 23, 2008

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Much of the code was inspired by Derek Yerger's code, though I don't
think much of that remains.  In any event that was..
    (copyleft) 2006 by Derek Yerger - Free to distribute freely.

The CRC code was excerpted and inspired by the Dallas Semiconductor
sample code bearing this copyright.
*/
//---------------------------------------------------------------------------
// Copyright (C) 2000 Dallas Semiconductor Corporation, All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL DALLAS SEMICONDUCTOR BE LIABLE FOR ANY CLAIM, DAMAGES
// OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// Except as contained in this notice, the name of Dallas Semiconductor
// shall not be used except as stated in the Dallas Semiconductor
// Branding Policy.
//--------------------------------------------------------------------------

#ifndef SNATCH59_ONEWIRECRC_H
#define SNATCH59_ONEWIRECRC_H

#include <avr/io.h>
#include <util/delay.h>
#include "IOport.h"
#include "wire1.h"

// Select the table-lookup method of computing the 8-bit CRC by setting this to 1
#ifndef ONEWIRE_CRC8_TABLE
#define ONEWIRE_CRC8_TABLE 1
#endif
typedef unsigned char BYTE;    // used to be uint8_t : something a byte wide, whatever ....

#define timing_0         3
#define timing_1        64
#define timing_2        60
#define timing_3        10
#define timing_4        10
#define timing_5        57
#define timing_6       480
#define timing_7        15
#define timing_8        70
#define timing_9       410

#define ADDRESS_CRC_BYTE 7


class OneWireCRC
{
public:
    OneWireCRC();

    // reset, read, write functions
    int reset();
    void writeByte(int data);
    int readByte();
    int touchByte(int data);
    void block(BYTE* data, int data_len);
    int readBit();

    // address functions
    void matchROM(BYTE rom[8]);
    void skipROM();

    // address search functions
    void resetSearch();
    BYTE search(BYTE* newAddr);

    // CRC check functions
    static BYTE crc8(BYTE* addr, BYTE len);
    static unsigned short crc16(unsigned short* data, unsigned short len);

//    enum eResolution {nineBit = 0, tenBit, elevenBit, twelveBit};
//    const int CONVERSION_TIME[4] = {94, 188, 375, 750};    // milli-seconds

private:
    const int* timing;

    int searchJunction;        // so we can set to it -1 somewhere
    bool searchExhausted;
    BYTE address[ADDRESS_CRC_BYTE + 1];

    // read/write bit functions
    void writeBit(int bit);
};

extern class OneWireCRC ONE_WIRE_CRC;
#endif
