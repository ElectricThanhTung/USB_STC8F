
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#define PORT        0xB0
#define P3M0        0xB2
#define P3M1        0xB1

NAME    USB_SEND_NACK

?PR?usb_send_nack?USB_SEND_NACK SEGMENT CODE
    PUBLIC usb_send_nack
    RSEG  ?PR?usb_send_nack?USB_SEND_NACK
usb_send_nack:
    ORL P3M0, #0x03     ; 1
    ANL P3M1, #0xFC     ; 1

    LCALL delay         ; 19
    //LCALL delay           ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19
    LCALL delay         ; 19
    NOP

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19
    LCALL delay         ; 19
    NOP

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19
    LCALL delay         ; 19
    LCALL delay         ; 19
    NOP
    NOP

    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19
    LCALL delay         ; 19
    NOP


    XRL PORT, #0x03     ; 1
    LCALL delay         ; 19

    ANL PORT, #0xFC     ; 1
    LCALL delay         ; 19
    LCALL delay         ; 19
    NOP

    ORL PORT, #0x01     ; 1
    ANL P3M0, #0xFC     ; 1
    ORL P3M1, #0x03     ; 1
    RET

delay:                  ; 19
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    RET

    END
