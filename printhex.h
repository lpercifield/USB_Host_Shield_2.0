/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#if !defined(__PRINTHEX_H__)
#define __PRINTHEX_H__

#if defined(ARDUINO) && ARDUINO >=100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define USB_HOST_SERIAL Serial

void E_Notifyc(char c, int lvl);

template <class T>
void PrintHex(T val, int lvl) {
//#ifdef DEBUG_USB_HOST
        int num_nibbles = sizeof(T) * 2;

        do {
                char v = 48 + (((val >> (num_nibbles - 1) * 4)) & 0x0f);
                if(v > 57) v += 7;
                E_Notifyc(v, lvl);
        } while(--num_nibbles);
//#endif
}

template <class T>
void PrintBin(T val, int lvl) {
//#ifdef DEBUG_USB_HOST
        for(T mask = (((T) 1) << ((sizeof(T) << 3) - 1)); mask; mask >>= 1)
                if(val & mask)
                        E_Notifyc('1', lvl);
                else
                        E_Notifyc('0', lvl);
//#endif
}

template <class T>
void SerialPrintHex(T val) {
//#ifdef DEBUG_USB_HOST
        int num_nibbles = sizeof(T) * 2;

        do {
                char v = 48 + (((val >> (num_nibbles - 1) * 4)) & 0x0f);
                if(v > 57) v += 7;
                USB_HOST_SERIAL.print(v);
        } while(--num_nibbles);
//#endif
}

template <class T>
void PrintHex2(Print *prn, T val) {
//#ifdef DEBUG_USB_HOST
        T mask = (((T) 1) << (((sizeof(T) << 1) - 1) << 2));

        while(mask > 1) {
                if(val < mask)
                        prn->print("0");

                mask >>= 4;
        }
        prn->print((T) val, HEX);
//#endif
}

#endif // __PRINTHEX_H__
