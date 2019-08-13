
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#include "main.h"

void GPIO_P1Mode(unsigned char PIN, GPIOMode mode) {
    if(mode & 0x01)
        P1M0 |= PIN;
    else
        P1M0 &= ~PIN;

    if(mode & 0x02)
        P1M1 |= PIN;
    else
        P1M1 &= ~PIN;
}

void GPIO_P3Mode(unsigned char PIN, GPIOMode mode) {
    if(mode & 0x01)
        P3M0 |= PIN;
    else
        P3M0 &= ~PIN;

    if(mode & 0x02)
        P3M1 |= PIN;
    else
        P3M1 &= ~PIN;
}

void GPIO_P5Mode(unsigned char PIN, GPIOMode mode) {
    if(mode & 0x01)
        P5M0 |= PIN;
    else
        P5M0 &= ~PIN;

    if(mode & 0x02)
        P5M1 |= PIN;
    else
        P5M1 &= ~PIN;
}
