
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#ifndef __GPIO_H__
#define __GPIO_H__

#define PIN0                    0x01
#define PIN1                    0x02
#define PIN2                    0x04
#define PIN3                    0x08
#define PIN4                    0x10
#define PIN5                    0x20
#define PIN6                    0x40
#define PIN7                    0x80

typedef enum {
    QUASI = 0,
    PUSHPULL = 1,
    OUTPUT = 1,
    INPUT = 2,
    OPENDRAIN = 3,
} GPIOMode;

void GPIO_P1Mode(unsigned char PIN, GPIOMode mode);
void GPIO_P3Mode(unsigned char PIN, GPIOMode mode);
void GPIO_P5Mode(unsigned char PIN, GPIOMode mode);

#endif
