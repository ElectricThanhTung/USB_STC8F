
#ifndef __USB_DESC_H__
#define __USB_DESC_H__

#include "usb_def.h"

static enum usb_settings {
    USB_VENDOR_ID = 0x1234,
    USB_DEVICE_ID = 0x5678,
    USB_DEVICE_VERSION = 0x9012,
};

static const unsigned char code usb_device_descriptor[] = {
    18,                                             // Size of the Descriptor in Bytes
    USBDESCR_DEVICE,                                // Device Descriptor (0x01)
    0x10,
    0x01,                                           // USB 1.1 = 0x0110, USB 1.0 = 0x0100
    0x00,                                           //0x00, // Class Code
    0x00,                                           // Subclass Code
    0x00,                                           // Protocol Code
    0x08,                                           // Maximum Packet Size for Zero Endpoint
    USB_VENDOR_ID,
    USB_VENDOR_ID >> 8,                             // VID
    USB_DEVICE_ID,
    USB_DEVICE_ID >> 8,                             // PID
    USB_DEVICE_VERSION,
    USB_DEVICE_VERSION >> 8,                        // Device Release Number
    0x01,                                           // Index of Manufacturer String Descriptor
    0x02,                                           // Index of Product String Descriptor
    0x03,                                           // Index of Serial Number String Descriptor
    0x01,                                           // Number of Possible Configurations
};

static const unsigned char code usb_report_descriptor[] = {
    0x05, 0x01,                                     // USAGE_PAGE (Generic Desktop)
    0x09, 0x00,                                     // USAGE (Undefined)
    0xA1, 0x01,                                     // COLLECTION (Application)
    0x15, 0x00,                                     // LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,                               // LOGICAL_MAXIMUM (255)

    0x75, 0x08,                                     //   REPORT_SIZE (8)

    0x85, 0x01,                                     // REPORT_ID (1)
    0x95, 0xF8,                                     // REPORT_COUNT (248)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x81, 0x02,                                     // INPUT (Data,Var,Abs,Vol) - to the host

    0x85, 0x02,                                     // REPORT_ID (2)
    0x95, 0x07,                                     // REPORT_COUNT (7)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0x85, 0x03,                                     // REPORT_ID (2)
    0x95, 0x0F,                                     // REPORT_COUNT (15)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0x85, 0x04,                                     // REPORT_ID (2)
    0x95, 0x1F,                                     // REPORT_COUNT (31)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0x85, 0x05,                                     // REPORT_ID (2)
    0x95, 0x3F,                                     // REPORT_COUNT (63)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0x85, 0x06,                                     // REPORT_ID (2)
    0x95, 0x7F,                                     // REPORT_COUNT (127)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0x85, 0x07,                                     // REPORT_ID (2)
    0x95, 0xF7,                                     // REPORT_COUNT (127)
    0x09, 0x00,                                     // USAGE (Undefined)
    0x91, 0x02,                                     // OUTPUT (Data,Var,Abs,Vol) - from the host

    0xC0                                            // END_COLLECTION
};

static const unsigned char code usb_configuration_descriptor[] = {
    9,                                              // Size of Descriptor in Bytes
    USBDESCR_CONFIG,                                // Configuration Descriptor (0x02)
    27, 0,                                          // Total length in bytes of data returned
    0x01,                                           // Number of Interfaces
    0x01,                                           // Value to use as an argument to select this configuration
    0x00,                                           // Index of String Descriptor describing this configuration
    USBATTR_BUSPOWER,                               // D7 Reserved, set to 1. (USB 1.0 Bus Powered), D6 Self Powered, D5 Remote Wakeup, D4..0 Reserved, set to 0.
    USB_CFG_MAX_BUS_POWER / 2,                      // Maximum Power Consumption in 2mA units

    // interface descriptor
    9,                                              // Size of Descriptor in Bytes (9 Bytes)
    USBDESCR_INTERFACE,                             // Interface Descriptor (0x04)
    0x00,                                           // Number of Interface
    0x00,                                           // Value used to select alternative setting
    0x00,                                           // Number of Endpoints used for this interface
    0x03,                                           // Class Code
    0x00,                                           // Subclass Code
    0x00,                                           // Protocol Code
    0x00,                                           // Index of String Descriptor Describing this interface

    // HID descriptor
    9,                                              // Size of Descriptor in Bytes (9 Bytes)
    USBDESCR_HID,                                   // HID descriptor (0x21)
    0x01,
    0x01,                                           // BCD representation of HID version
    0x00,                                           // Target country code
    0x01,                                           // Number of HID Report (or other HID class) Descriptor infos to follow
    0x22,                                           // Descriptor type: report
    ARRAY_LENGHT(usb_report_descriptor),
    ARRAY_LENGHT(usb_report_descriptor) >> 8,       // total length of report descriptor

    // Endpoint descriptor
    // 7,                                           // Size of Descriptor in Bytes (7 Bytes)
    // USBDESCR_ENDPOINT,                           // Endpoint descriptor (0x05)
    // 0x81,                                        // IN endpoint number 1 (0x81)
    // 0x03,                                        // attrib: Interrupt endpoint
    // 0x08,
    // 0x00,                                        // maximum packet size
    // 0x01,                                        // POLL INTERVAL (ms)

    // 7,                                           // Size of Descriptor in Bytes (7 Bytes)
    // USBDESCR_ENDPOINT,                           // Endpoint descriptor (0x05)
    // 0x01,                                        // OUT endpoint number 1 (0x81)
    // 0x03,                                        // attrib: Interrupt endpoint
    // 0x08,
    // 0x00,                                        // maximum packet size
    // 0x01,                                        // POLL INTERVAL (ms)
};

static const unsigned char code usb_string_descriptor_language[] = {
    4,
    USBDESCR_STRING,
    0x09, 0x04,
};

static const unsigned char code usb_string_descriptor_vendor[] = {
    22,
    USBDESCR_STRING,
    'T', 0,
    'h', 0,
    'a', 0,
    'n', 0,
    'h', 0,
    ' ', 0,
    'T', 0,
    0xF9, 0,
    'n', 0,
    'g', 0,
};

static const unsigned char code usb_string_descriptor_device[] = {
    26,
    USBDESCR_STRING,
    'S', 0,
    'T', 0,
    'C', 0,
    '8', 0,
    'F', 0,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0,
    'H', 0,
    'I', 0,
    'D', 0,
};

static const unsigned char code usb_string_descriptor_serial[] = {
    22,
    USBDESCR_STRING,
    '2', 0,
    '1', 0,
    '-', 0,
    '0', 0,
    '3', 0,
    '-', 0,
    '2', 0,
    '0', 0,
    '1', 0,
    '9', 0,
};

#endif
