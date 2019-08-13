
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#ifndef __USB_SOFT_H__
#define __USB_SOFT_H__

#define TimerTickStep           20

void USB_Init(void);
void USB_Disconnect(void);
void USB_SendData(unsigned char *buffer, unsigned char length) reentrant;
void USB_WriteBuf(unsigned char *buffer, unsigned char length) reentrant;

#endif
