
// Written By       : Thanh Tung
// E-Mail           : electricthanhtung@gmail.com
// Facebook         : https://www.facebook.com/electricthanhtung

// MCU              : STC8F Family
// P3.0             : D-
// P3.1 and P3.2    : D+
// Frequency        : 27MHz

#include "main.h"
#include "usb.h"

void USB_Received(unsigned char endpoint, unsigned char *buffer, unsigned char length) reentrant {

}

void main() {
    USB_Disconnect();
    delay_ms(50);
    USB_Init();
    while(1) {
        PCON |= 0x01;       // CPU sleep
    }
}
