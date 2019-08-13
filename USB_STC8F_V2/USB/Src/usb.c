
// Written By : Thanh Tung
// E-Mail     : electricthanhtung@gmail.com
// Facebook   : https://www.facebook.com/electricthanhtung

#include "main.h"
#include "usb.h"
#include "usb_desc.h"

volatile unsigned char data usb_rx_buffer[12];
volatile unsigned char xdata usb_tx_buffer[12];
volatile unsigned char data usb_tx_count = 0, usb_rx_count = 0;
volatile unsigned char data UEPF = 1, UDRF = 1;
volatile unsigned char xdata USB_TimerTick = 0;     // 20ms
static volatile unsigned char xdata rx_buffer[250];
static unsigned char xdata data_sync;

static data struct usb_type {
    volatile unsigned char state;
    volatile unsigned char event;
    volatile unsigned char device_address;

    volatile unsigned char received;
    volatile unsigned char ack;

    unsigned char endpoint;

    volatile unsigned int wLength;
} usb = {0, 0, 0, 0, 0, 0, 0xFF};

extern void usb_send_ack();
extern void usb_send_nack();

static void usb_send_answer() {
    extern void usb_tx();
    P3 = (P3 & 0xFC) | 0x01;
    P3M0 |= 0x03;
    P3M1 &= ~0x03;
    usb_tx();
    P3M0 &= ~0x03;
    P3M1 |= 0x03;
}

static void usb_received_reentrant() reentrant {
    static unsigned char data data_count = 0, pid_data_old;
    UDRF = 0;
    if(usb_rx_buffer[1] == USB_PID_OUT) {
        unsigned char address = usb_rx_buffer[2] & 0x7F;
        if((address == usb.device_address) || (address == 0)) {
            usb.state = USB_STATE_OUT;
            usb.endpoint = usb_rx_buffer[2] >> 7;
            usb.endpoint |= ((usb_rx_buffer[3] & 0x07) << 1);
        }
    }
    else if(usb_rx_buffer[1] == USB_PID_SETUP) {
        //usb.state = USB_STATE_SETUP;
        unsigned char address = usb_rx_buffer[2] & 0x7F;
        if((address == usb.device_address) || (address == 0)) {
            usb.state = USB_STATE_SETUP;
            usb.endpoint = usb_rx_buffer[2] >> 7;
            usb.endpoint |= ((usb_rx_buffer[3] & 0x07) << 1);
        }
        return;
    }
    else switch(usb_rx_buffer[1]) {
    case USB_PID_IN: {
        unsigned char address = usb_rx_buffer[2] & 0x7F;
        if((address != usb.device_address) && (address != 0))
            return;
        if(usb_tx_count) {
            usb_send_answer();
            usb_tx_count = 0;
        }
        //if(usb.event == USB_EVENT_READY_DATA_IN) {
        //  usb_send_answer();
        //  usb.event = USB_EVENT_WAIT_DATA_IN;
        //}
        else
            usb_send_nack();
        usb.state = USB_STATE_IN;
        break;
    }
    case USB_PID_DATA0: {
        if(usb.state == USB_STATE_OUT) {
            if(pid_data_old == USB_PID_DATA1) {
                unsigned char xdata *buffer = &rx_buffer[data_count];
                buffer[0] = usb_rx_buffer[2];
                buffer[1] = usb_rx_buffer[3];
                buffer[2] = usb_rx_buffer[4];
                buffer[3] = usb_rx_buffer[5];
                buffer[4] = usb_rx_buffer[6];
                buffer[5] = usb_rx_buffer[7];
                buffer[6] = usb_rx_buffer[8];
                buffer[7] = usb_rx_buffer[9];
                usb_send_ack();
                data_count += 8;
                if(data_count >= usb.wLength) {
                    usb.received = 1;
                    usb_tx_count = 0;
                    UDRF = 1;
                }
                pid_data_old = USB_PID_DATA0;
            }
            else {
                delay_us(1);
                usb_send_ack();
            }
            usb.event = USB_EVENT_NO;
        }
        else {
            rx_buffer[2] = usb_rx_buffer[2];
            rx_buffer[3] = usb_rx_buffer[3];
            rx_buffer[4] = usb_rx_buffer[4];
            rx_buffer[5] = usb_rx_buffer[5];
            rx_buffer[6] = usb_rx_buffer[6];
            rx_buffer[7] = usb_rx_buffer[7];
            rx_buffer[8] = usb_rx_buffer[8];
            pid_data_old = USB_PID_DATA0;
            data_count = 0;
            usb.event = USB_EVENT_RECEIVE_SETUP_DATA;
            if((usb_rx_buffer[2] != 0x21) && (usb_rx_buffer[3] != 0x09))
                UDRF = 1;
            //UDRF = 1;
            usb_send_ack();

            //wLength = usb_rx_buffer[9];
            //wLength = (wLength << 8) | usb_rx_buffer[8];

            usb.wLength = usb_rx_buffer[8];
        }
        break;
    }
    case USB_PID_DATA1:
        if (usb.state == USB_STATE_OUT) {
            if(usb_rx_count > 4) {
                if(pid_data_old == USB_PID_DATA0) {
                    unsigned char xdata *buffer = &rx_buffer[data_count];
                    buffer[0] = usb_rx_buffer[2];
                    buffer[1] = usb_rx_buffer[3];
                    buffer[2] = usb_rx_buffer[4];
                    buffer[3] = usb_rx_buffer[5];
                    buffer[4] = usb_rx_buffer[6];
                    buffer[5] = usb_rx_buffer[7];
                    buffer[6] = usb_rx_buffer[8];
                    buffer[7] = usb_rx_buffer[9];
                    usb_send_ack();
                    data_count += 8;
                    if(data_count >= usb.wLength) {
                        usb.received = 1;
                        usb_tx_count = 0;
                        UDRF = 1;
                    }
                    pid_data_old = USB_PID_DATA1;
                }
                else {
                    delay_us(1);
                    usb_send_ack();
                }
                usb.event = USB_EVENT_NO;
            }
            else {
                usb_tx_count = 0;
                delay_us(1);
                usb.state = USB_STATE_IDLE;
                usb_send_ack();
            }
        }
        break;
    case USB_PID_ACK:
        usb.ack = 1;
        break;
    case USB_PID_NACK:
        break;
    default:
        usb.state = USB_STATE_IDLE;
        break;
    }
}

void usb_received() {
    usb_received_reentrant();
}

const unsigned int code table[] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

void usb_calc_crc16(unsigned char length) reentrant {
    unsigned int crc = 0xFFFF;
    unsigned char i = 2;
    while(length--) {
        crc = table[(crc ^ usb_tx_buffer[i]) & 0xFF] ^ (crc >> 8);
        i++;
    }
    crc = ~crc;
    usb_tx_buffer[i] = crc;
    usb_tx_buffer[i + 1] = crc >> 8;
}

//static void usb_calc_crc16(unsigned char length) {
//  unsigned int data crc = 0xFFFF;
//  unsigned char data index;
//  for(index = 0; index < length; index++) {
//      unsigned char data i;
//    crc ^= usb_tx_buffer[index + 2];
//    for (i = 8; i--;) {
//      if (crc & 0x01) {
//        crc >>= 1;
//        crc ^= 0xA001;
//      }
//      else
//        crc >>= 1;
//    }
//  }
//  crc = ~crc;
//  usb_tx_buffer[index + 2] = (unsigned char)crc;
//  usb_tx_buffer[index + 3] = (unsigned char)(crc >> 8);
//}

void USB_SendData(unsigned char *buffer, unsigned char length) reentrant {
    unsigned char timeStart;
    usb.state = USB_STATE_IN;
    usb_tx_buffer[0] = 0x80;
    data_sync = USB_PID_DATA1;
    while(length) {
        usb_tx_buffer[1] = data_sync;
        if(data_sync == USB_PID_DATA1)
            data_sync = USB_PID_DATA0;
        else
            data_sync = USB_PID_DATA1;
        if(length >= 8) {
            unsigned char i;
            for(i = 0; i < 8; i++)
                usb_tx_buffer[i + 2] = buffer[i];
            buffer += 8;
            usb_calc_crc16(8);
            usb_tx_count = 12;
            length -= 8;
        }
        else {
            unsigned char i;
            for(i = 2; i < (length + 2); i++)
                usb_tx_buffer[i] = *buffer++;
            usb_calc_crc16(length);
            usb_tx_count = length + 4;
            length = 0;
        }

        timeStart = USB_TimerTick;
        while(usb_tx_count) {
            if((usb.state != USB_STATE_IN) || ((unsigned char)(USB_TimerTick - timeStart) > (100 / TimerTickStep))) {
                usb_tx_count = 0;
                return;
            }
        }

        //usb.event = USB_EVENT_READY_DATA_IN;
        //while(usb.event != USB_EVENT_WAIT_DATA_IN);
  }
}

void USB_WriteBuf(unsigned char *buffer, unsigned char length) reentrant {
    unsigned char start = 0;
    unsigned char timeStart;
    usb_tx_buffer[0] = 0x80;
    data_sync = USB_PID_DATA1;
    while(length) {
        usb_tx_buffer[1] = data_sync;
        if(data_sync == USB_PID_DATA1)
            data_sync = USB_PID_DATA0;
        else
            data_sync = USB_PID_DATA1;

        if(!start) {
            start = 1;
            usb_tx_buffer[2] = length;

            if((length % 8) == 7)
                length++;

            if(length >= 7) {
                unsigned char i;
                for(i = 0; i < 7; i++)
                    usb_tx_buffer[i + 3] = buffer[i];
                buffer += 7;
                usb_calc_crc16(8);
                usb_tx_count = 12;
                length -= 7;
            }
            else {
                unsigned char i;
                for(i = 3; i < (length + 3); i++)
                    usb_tx_buffer[i] = *buffer++;
                usb_calc_crc16(length + 1);
                usb_tx_count = length + 5;
                length = 0;
            }
        }
        else if(length >= 8) {
            unsigned char i;
            for(i = 0; i < 8; i++)
                usb_tx_buffer[i + 2] = buffer[i];
            buffer += 8;
            usb_calc_crc16(8);
            usb_tx_count = 12;
            length -= 8;
        }
        else {
            unsigned char data i;
            for(i = 2; i < (length + 2); i++)
                usb_tx_buffer[i] = *buffer++;
            usb_calc_crc16(length);
            usb_tx_count = length + 4;
            length = 0;
        }

        timeStart = USB_TimerTick;
        while(usb_tx_count) {
            if((unsigned char)(USB_TimerTick - timeStart) > (100 / TimerTickStep)) {
                usb_tx_count = 0;
                return;
            }
        }
    }
}

static void USB_SendNull(unsigned char PID_DATA) reentrant {
    unsigned char timeStart;
    usb.state = USB_STATE_IN;
    usb_tx_buffer[0] = 0x80;
    usb_tx_buffer[1] = PID_DATA;
    usb_tx_buffer[2] = 0;
    usb_tx_buffer[3] = 0;
    usb_tx_count = 4;

    timeStart = USB_TimerTick;
    while(usb_tx_count) {
        if((usb.state != USB_STATE_IN) || ((unsigned char)(USB_TimerTick - timeStart) > (100 / TimerTickStep))) {
            usb_tx_count = 0;
            return;
        }
    }
}

static void usb_send_stall() {
    usb_tx_buffer[0] = 0x80;
    usb_tx_buffer[1] = USB_PID_STALL;
    usb_tx_count = 2;
}

void USB_Process() {
  if(usb.event == USB_EVENT_RECEIVE_SETUP_DATA) {
        usb.event = USB_EVENT_NO;
        if(rx_buffer[2] == USBRQ_STD_FROM_DEVICE) {
            if(rx_buffer[3] == USBRQ_GET_DESCRIPTOR) {
                switch(rx_buffer[5]) {
                case USBDESCR_DEVICE:
                    USB_SendData((unsigned char *)usb_device_descriptor, ARRAY_LENGHT(usb_device_descriptor));
                    break;
                case USBDESCR_CONFIG:
                    if(rx_buffer[8] < ARRAY_LENGHT(usb_configuration_descriptor))
                        USB_SendData((unsigned char *)usb_configuration_descriptor, rx_buffer[8]);
                    else
                        USB_SendData((unsigned char *)usb_configuration_descriptor, ARRAY_LENGHT(usb_configuration_descriptor));
                    break;
                case USBDESCR_STRING:
                    if(rx_buffer[4] == 0) {
                        USB_SendData((unsigned char *)usb_string_descriptor_language, ARRAY_LENGHT(usb_string_descriptor_language));
                        USB_SendNull(data_sync);
                    }
                    else if(rx_buffer[4] == 1) {
                        USB_SendData((unsigned char *)usb_string_descriptor_vendor, ARRAY_LENGHT(usb_string_descriptor_vendor));
                        USB_SendNull(data_sync);
                    }
                    else if(rx_buffer[4] == 2) {
                        USB_SendData((unsigned char *)usb_string_descriptor_device, ARRAY_LENGHT(usb_string_descriptor_device));
                        USB_SendNull(data_sync);
                    }
                    else if(rx_buffer[4] == 3) {
                        USB_SendData((unsigned char *)usb_string_descriptor_serial, ARRAY_LENGHT(usb_string_descriptor_serial));
                        USB_SendNull(data_sync);
                    }
                    else
                        USB_SendNull(USB_PID_DATA1);
                    break;
                default:
                        break;
                }
            }
            else if(rx_buffer[3] == USBRQ_GET_STATUS) {
                usb_send_stall();
            }
        }
        else if(rx_buffer[2] == USBRQ_STD_TO_DEVICE) {
            switch(rx_buffer[3]) {
                case USBRQ_SET_ADDRESS:
                    if(usb.device_address != 0) {
                        //
                    }
                    USB_SendNull(USB_PID_DATA1);
                    usb.device_address = rx_buffer[4];
                    break;
                case (USBRQ_SET_CONFIGURATION):
                    USB_SendNull(USB_PID_DATA1);
                    break;
            }
        }
        else if (rx_buffer[2] == USBRQ_STD_FROM_INTERFACE) {
            if(rx_buffer[3] == USBRQ_GET_DESCRIPTOR)
                USB_SendData((unsigned char *)usb_report_descriptor, ARRAY_LENGHT(usb_report_descriptor));
        }
        else if(rx_buffer[2] == USBRQ_CLASS_TO_INTERFACE) {
            if(rx_buffer[3] == 0x0A)
                usb_send_stall();
        }
        else if(rx_buffer[2] == USBRQ_CLASS_FROM_INTERFACE) {
//          static const unsigned char code usb_report_null[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//          USB_SendData((unsigned char *)usb_report_null, ARRAY_LENGHT(usb_report_null));
        }
    }
    if(usb.received) {
        extern void USB_Received(unsigned char endpoint, unsigned char *buffer, unsigned char length) reentrant;
        unsigned char xdata timeStart;
        usb.ack = 0;
        USB_SendNull(USB_PID_DATA1);
        timeStart = USB_TimerTick;
        usb.received = 0;
        usb.event = USB_EVENT_NO;
        while(!usb.ack) {
            if((unsigned char)(USB_TimerTick - timeStart) > 5)
                return;
        }
        USB_Received(usb.endpoint, rx_buffer, usb.wLength);
    }
}
