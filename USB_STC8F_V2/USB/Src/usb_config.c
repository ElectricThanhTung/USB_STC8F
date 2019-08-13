
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#include "main.h"

static void GPIO_Init() {
    P3 = (P3 & 0xFC) | 0x01;
    GPIO_P3Mode(PIN0 | PIN1 | PIN2, INPUT);
}

static void EXTI_Init() {
//  INTCLKO |= EX4;
//  IE |= 0x80;
    IP |= 0x01;
    IPH |= 0x01;
    IT0 = 1;
    IE |=0x81;
}

void USB_Disconnect() {
    EX0 = 0;
    P3 &= 0xFC;
    GPIO_P3Mode(PIN0 | PIN1, OUTPUT);
}

void USB_Init() {
    GPIO_Init();
    EXTI_Init();
}
