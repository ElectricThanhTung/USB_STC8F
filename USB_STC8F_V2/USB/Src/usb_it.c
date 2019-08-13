
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#include "main.h"

void INT3_ISR() interrupt 0 {
    extern void usb_rx();
    EA = 0;
    usb_rx();
    IE0 = 0;
    EA = 1;
}
