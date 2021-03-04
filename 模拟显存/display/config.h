#ifndef _CONFIG_H
#define _CONFIG_H

#define SDA_PIN 22
#define SCL_PIN 20

#define LED 3

#define A0  14
#define A1  15
#define A2  16
#define A3  17
#define A4  18
#define A5  19

#define A7  7
#define A8  6
#define A9  5
#define A10 4
#define A11 24
#define A12 2

#define IO0 8
#define IO1 9
#define IO2 10
#define IO3 11
#define IO4 12
#define IO5 13
#define IO6 23
#define IO7 21

#define CE  3
#define WE  26
#define OE  25

#define ReadCE digitalRead(CE)
#define ReadOE digitalRead(OE)
#define ReadWE digitalRead(WE)

#define DISPLAY_ASCII_WIDTH  25
#define DISPLAY_ASCII_HEIGHT 8

#define DISPLAY_CHAR_WIDTH  5
#define DISPLAY_CHAR_HEIGHT 8

#endif

