// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#include "main.h"

void delay_us(unsigned int time) {
    while(time--) {
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
        _nop_(); _nop_();
    }
}

void delay_ms(unsigned int time) {
    while(time--)
        delay_us(999);
}
