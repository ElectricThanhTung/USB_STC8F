
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
//            : yeulahettientieu@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#define PORT        0xB0

NAME    USB_TX_2

?PR?usb_tx_2?USB_TX_2 SEGMENT CODE
    EXTRN   DATA (usb_tx_count_2)
    EXTRN   XDATA (usb_tx_buffer_2)
    PUBLIC usb_tx_2
    RSEG  ?PR?usb_tx_2?USB_TX_2
usb_tx_2:
    ;LCALL delay
    ;LCALL delay
    MOV R0, #0x06
    MOV DPTR, #usb_tx_buffer_2
    MOV R2, usb_tx_count_2
    MOVX A, @DPTR                 ; 2
    LJMP bit0

delay:
    NOP
    NOP
    NOP
    NOP
    RET

bit0:
    RRC A                         ; 1
    JC bit0Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    INC DPTR                      ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    SJMP bit1                     ; 3
bit0Idle:
    LCALL delay                   ; 10
    INC DPTR                      ; 1
    NOP
    NOP
    DJNZ R0, bit1                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit1:
    RRC A                         ; 1
    JC bit1Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit2                     ; 3
bit1Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit2                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit2:
    RRC A                         ; 1
    JC bit2Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit3                     ; 3
bit2Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit3                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit3:
    RRC A                         ; 1
    JC bit3Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit4                     ; 3
bit3Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit4                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit4:
    RRC A                         ; 1
    JC bit4Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit5                     ; 3
bit4Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit5                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit5:
    RRC A                         ; 1
    JC bit5Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit6                     ; 3
bit5Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit6                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit6:
    RRC A                         ; 1
    JC bit6Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    SJMP bit7                     ; 3
bit6Idle:
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    DJNZ R0, bit7                 ; 2/3
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
bit7:
    RRC A                         ; 1
    JC bit7Idle                   ; 1/3
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    MOVX A, @DPTR                 ; 2
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R2, goto_bit0            ; 2/3
    NOP
    SJMP END_TX

bit7Idle:
    DJNZ R2, nextbyte             ; 2/3
    LCALL delay                   ; 10
    NOP
    SJMP END_TX                   ; 3

nextbyte:
    MOVX A, @DPTR                 ; 2
    NOP
    NOP
    NOP
    NOP
    NOP
    DJNZ R0, goto_bit0            ; 2/3
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    XRL PORT, #0x03               ; 1
    MOV R0, #0x06                 ; 1
    LCALL delay                   ; 10
    LJMP bit0                     ; 3
goto_bit0:
    LJMP bit0                     ; 3
END_TX:
    NOP
    NOP
    ANL PORT, #0xFC               ; 1
    LCALL delay                   ; 10
    LCALL delay                   ; 10
    LCALL delay                   ; 10
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    ORL PORT, #0x01               ; 1
    RET

    END
