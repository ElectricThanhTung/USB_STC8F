
#ifndef __USB_DEF_H__
#define __USB_DEF_H__

#define ARRAY_LENGHT(Value)         (sizeof(Value) / sizeof(Value[0]))

static enum usb_pid_list {
    USB_PID_SETUP = 0x2D,
    USB_PID_DATA0 = 0xC3,
    USB_PID_DATA1 = 0x4B,
    USB_PID_IN = 0x69,
    USB_PID_OUT = 0xE1,
    USB_PID_ACK = 0xD2,
    USB_PID_NACK = 0x5A,
    USB_PID_STALL = 0x1E
};

static enum usb_states_list {
    USB_STATE_IDLE = 0,
    USB_STATE_SETUP = 1,
    USB_STATE_IN = 2,
    USB_STATE_OUT = 3,
    USB_STATE_DATA = 4,
    USB_STATE_ADDRESS_CHANGE = 5
};

static enum usb_events_list {
    USB_EVENT_NO = 0,
    USB_EVENT_RECEIVE_SETUP_DATA = 1,
    USB_EVENT_READY_DATA_IN = 2,
    USB_EVENT_WAIT_DATA_IN = 3,
};

static enum usb_request_standart_type_list {
    USBRQ_STD_TO_DEVICE = 0x00,
    USBRQ_STD_TO_INTERFACE = 0x01,
    USBRQ_STD_TO_ENDPOINT = 0x02,
    USBRQ_STD_FROM_DEVICE = 0x80,
    USBRQ_STD_FROM_INTERFACE = 0x81,
    USBRQ_STD_FROM_ENDPOINT = 0x82,

    USBRQ_CLASS_TO_DEVICE = 0x20,
    USBRQ_CLASS_TO_INTERFACE = 0x21,
    USBRQ_CLASS_TO_ENDPOINT = 0x22,
    USBRQ_CLASS_FROM_DEVICE = 0xa0,
    USBRQ_CLASS_FROM_INTERFACE = 0xa1,
    USBRQ_CLASS_FROM_ENDPOINT = 0xa2,

    USBRQ_VENDOR_TO_DEVICE = 0x40,
    USBRQ_VENDOR_TO_INTERFACE = 0x41,
    USBRQ_VENDOR_TO_ENDPOINT = 0x42,
    USBRQ_VENDOR_FROM_DEVICE = 0xc0,
    USBRQ_VENDOR_FROM_INTERFACE = 0xc1,
    USBRQ_VENDOR_FROM_ENDPOINT = 0xc2,

    USBRQ_CLASS=0x20,
    USBRQ_VENDOR=0x40
};

static enum usb_request {
    USBRQ_GET_STATUS = 0x00,
    USBRQ_CLEAR_FEATURE = 0x01,
    USBRQ_SET_FEATURE = 0x03,
    USBRQ_SET_ADDRESS = 0x05,
    USBRQ_GET_DESCRIPTOR = 0x06,
    USBRQ_SET_DESCRIPTOR = 0x07,
    USBRQ_GET_CONFIGURATION = 0x08,
    USBRQ_SET_CONFIGURATION = 0x09,
    USBRQ_GET_INTERFACE = 0x0a,
    USBRQ_SET_INTERFACE = 0x0b,
    USBRQ_SYNCH_FRAME = 0x0c
};

static enum descriptor_Type {
    USBDESCR_DEVICE = 0x01,
    USBDESCR_CONFIG = 0x02,
    USBDESCR_STRING = 0x03,
    USBDESCR_INTERFACE = 0x04,
    USBDESCR_ENDPOINT = 0x05,
    USBDESCR_HID = 0x21,
    USBDESCR_HID_REPORT = 0x22,
    USBDESCR_HID_PHYS = 0x23
};

static enum USB_Power {
    USBATTR_BUSPOWER = 0x80,  // USB 1.1 does not define this value any more
    USBATTR_SELFPOWER = 0x40,
    USBATTR_REMOTEWAKE = 0x20,
    USB_CFG_MAX_BUS_POWER = 100,
};

#endif
