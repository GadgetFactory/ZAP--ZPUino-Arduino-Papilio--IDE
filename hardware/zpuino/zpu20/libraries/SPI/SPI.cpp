/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * Copyright (c) 2013 by Alvaro Lopes <alvieboy@alvie.com>
 *
 * SPI Master library for zpuino, based on arduino's library by Cristian Maglie.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"
#include <Arduino.h>

SPIClass SPI;

#define VENDOR_ZPUINO       0x08
#define PRODUCT_ZPUINO_SPI  0x10

#define PPS_INDEX_MOSI 0
#define PPS_INDEX_SCK  1
#define PPS_INDEX_MISO 0

void SPIClass::begin(MOSI mosi, MISO miso, SCK sck)
{
    if (deviceBegin(VENDOR_ZPUINO, PRODUCT_ZPUINO_SPI)!=0) {
        return;
    }

    Serial.println(getSlot());
    REG(0)=BIT(SPICP1)|BIT(SPIEN)|BIT(SPIBLOCK);

    pinMode(mosi, OUTPUT);
    pinMode(miso, INPUT);
    pinMode(sck, OUTPUT);

    pinModePPS(sck,HIGH);
    pinModePPS(mosi,HIGH);

    int ppspin = DeviceRegistry::getPPSOutputPin( getSlot(), PPS_INDEX_MOSI );
    outputPinForFunction( mosi, ppspin );
    ppspin = DeviceRegistry::getPPSOutputPin( getSlot(), PPS_INDEX_SCK );
    outputPinForFunction( sck, ppspin);
    ppspin = DeviceRegistry::getPPSInputPin( getSlot(), PPS_INDEX_MISO );
    inputPinForFunction( miso, ppspin );
}

byte SPIClass::transfer(unsigned _data) {
    REG(1) = _data;
    return REG(1);
}

uint16_t SPIClass::transfer16(unsigned _data) {
    REG(3) = _data;
    return REG(3);
}

uint32_t SPIClass::transfer32(unsigned _data) {
    REG(5) = _data;
    return REG(5);
}

void SPIClass::end() {
    REG(0) = REG(0) &  ~(_BV(SPIEN)|_BV(SPIBLOCK));
}

void SPIClass::setBitOrder(int bitOrder)
{
	/* No support */
}

void SPIClass::setDataMode(int mode)
{
    REG(0) = (REG(0) & ~SPI_MODE_MASK) | mode;
}

void SPIClass::setClockDivider(int rate)
{
    REG(0) = (REG(0) & ~SPI_CLOCK_MASK) | rate;
}


SPIClass::SPIClass(int index): BaseDevice(index)
{
}
