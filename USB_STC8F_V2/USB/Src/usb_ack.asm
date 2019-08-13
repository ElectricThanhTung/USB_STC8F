
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#define PORT        0xB0
#define P3M0        0xB2
#define P3M1        0xB1

NAME    USB_SEND_ACK

?PR?usb_send_ack?USB_SEND_ACK SEGMENT CODE
    PUBLIC usb_send_ack
    RSEG  ?PR?usb_send_ack?USB_SEND_ACK
usb_send_ack:
    ORL P3M0, #0x03     ; 1
    ANL P3M1, #0xFC     ; 1

    //LCALL delay           ; 19
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
