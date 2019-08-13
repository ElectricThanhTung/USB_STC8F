
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#define PORT        0xB0

NAME    GOTO_USB_PROCESS

?PR?goto_usb_process?GOTO_USB_PROCESS SEGMENT CODE
    EXTRN   DATA (UEPF)
    EXTRN   CODE (USB_Process)
    PUBLIC goto_usb_process
    RSEG  ?PR?goto_usb_process?GOTO_USB_PROCESS

goto_usb_process:
    ;POP ACC
    ;POP ACC
    LCALL USB_Process
    POP 0x07
    POP 0x06
    POP 0x05
    POP 0x04
    POP 0x03
    POP 0x02
    POP 0x01
    POP 0x00
    POP PSW
    POP DPL
    POP DPH
    POP B
    POP ACC
    MOV UEPF, #1
    RET

    END
