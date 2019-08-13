
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#define DEBUG           0           // 0: Turn off debug, 1: Turn on debug

#define PORT            0xB0

NAME    USB_RX

?PR?usb_rx?USB_RX SEGMENT CODE
    EXTRN   DATA (usb_rx_buffer, usb_rx_count, UEPF, UDRF)
    EXTRN   CODE (usb_received)
    EXTRN   CODE (goto_usb_process)
    PUBLIC usb_rx
    RSEG  ?PR?usb_rx?USB_RX
usb_rx:
    MOV A, #9
delay:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    DEC A
    JNZ delay

    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

    MOV R3, #0x06
    MOV R2, #0x01
    MOV R1, #usb_rx_buffer
    MOV R0, #12
    MOV @R1, #0x80

    LJMP bit0

bit7:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END1_RX                            ; 1/3
    XRL A, R2                             ; 1

    RRC A
    RRC A
    MOV @R1, A
    RLC A
    CLR 0xE0.1
    MOV R2, A                             ; 10

    NOP
    JNC next7

    NOP
    NOP
    NOP
    DJNZ R3, bit0                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit0                             ; 3
next7:
    MOV R3, #0x06                         ; 1
    LJMP bit0

bit0:
#if DEBUG
    CPL 0xB0.7
#else
    NOP
#endif
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END1_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    INC R1                                ; 1

    MOV A, R0                             ; 1
    JZ END1_RX                            ; 1/3

    NOP
    JNC next0
    NOP
    NOP                                   ; 15
    DJNZ R3, bit1                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit1                             ; 3
next0:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
bit1:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END1_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    NOP                                   ; 1

    NOP
    JNC next1
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R3, bit2                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit2                             ; 3
next1:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    LJMP bit2

END1_RX:
    MOV A, #13
    CLR C
    SUBB A, R0
    MOV usb_rx_count, A
    LCALL usb_received
    MOV A, UDRF
    ANL A, UEPF
    JNZ goto_usb_process1
    RET
goto_usb_process1:
    CLR 0x88.1
    SETB 0xA8.7
    MOV UEPF, #0
    POP ACC
    POP ACC

    MOV DPTR, #goto_usb_process
    PUSH DPL
    PUSH DPH
    MOV PSW, #0
    RETI

bit2:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END1_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    NOP

    NOP
    JNC next2
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R3, bit3                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit3                             ; 3
next2:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    NOP
    NOP
    NOP
bit3:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END1_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    NOP

    NOP
    JNC next3
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R3, bit4                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit4                             ; 3
next3:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    NOP
    NOP
    NOP

bit4:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END2_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    NOP

    NOP
    JNC next4
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R3, bit5                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit5                             ; 3
next4:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    NOP
    NOP
    NOP
bit5:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END2_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    NOP

    NOP
    JNC next5
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R3, bit6                         ; 2/3
    LCALL bit_idle                        ;
    LJMP bit6                             ; 3
next5:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    LJMP bit6

END2_RX:
    MOV A, #13
    CLR C
    SUBB A, R0
    MOV usb_rx_count, A
    LCALL usb_received
    MOV A, UDRF
    ANL A, UEPF
    JNZ goto_usb_process2
    RET
goto_usb_process2:
    CLR 0x88.1
    SETB 0xA8.7
    MOV UEPF, #0
    POP ACC
    POP ACC

    MOV DPTR, #goto_usb_process
    PUSH DPL
    PUSH DPH
    MOV PSW, #0
    RETI

bit6:
    MOV A, PORT                           ; 1
    ANL A, #0x03                          ; 1
    JZ END2_RX                            ; 1/3
    XRL A, R2                             ; 1
    CLR 0xE0.2                            ; 1
    RRC A                                 ; 1
    MOV R2, A                             ; 1
    DEC R0                                ; 1

    NOP
    JNC next6
    NOP
    NOP
    DJNZ R3, goto_bit7                    ; 2/3
    NOP
    NOP
    NOP
    LCALL bit_idle                        ;
    LJMP bit7                             ; 3
goto_bit7:
    LJMP bit7

next6:
    MOV R3, #0x06                         ; 1
    NOP
    NOP
    LJMP bit7

bit_idle:
    MOV R3, #0x06
#if DEBUG
    CPL 0xB0.6
#else
    NOP
#endif
    MOV A, R2
    CPL 0xE0.0
    MOV R2, A
    NOP
    NOP
    NOP
    NOP
    NOP
    ;NOP
    ;NOP
    RET

    END
