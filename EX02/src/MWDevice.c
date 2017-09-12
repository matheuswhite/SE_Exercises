#include "../inc/MWDevice.h"

const char* MWDeviceStatus2String(MWDeviceStatus status) {
    switch (status) {
        case kDesconnected:
            return "Desconnected";
            break;
        case kConnected:
            return "Connected";
            break;
        default:
            return "Unknown";
            break;
        }
}

void MWDeviceCopy(MWDevice *dst, MWDevice *src) {
    dst->name = src->name;
    dst->battery = src->battery;
    dst->signalStrength = src->signalStrength;
    dst->status = src->status;
    dst->dataBuffer = src->dataBuffer;
}

void MWDeviceShow(MWDevice *device, MWPrint function) {
    char buffer[2048];
    MWDevice2String(device, buffer);
    function(buffer);
}

void MWDevice2String(MWDevice *device, char *buffer) {
    char s_battery[3];
    char s_signalStrength[3];
    char s_status[12];
    char s_dataBuffer[DATABUFFERMAXSIZE << 2];
    char s_data[6];
    int i;

    //battery
    sprintf(s_battery, "%d", device->battery);
    //signalStrength
    sprintf(s_signalStrength, "%d", device->signalStrength);
    //status
    sprintf(s_status, "%s", MWDeviceStatus2String(device->status));
    //dataBuffer
    for (i = 0; i < device->dataBufferSize; ++i) {
        sprintf(s_data, "0x%x, ", device->dataBuffer[i]);
        strcat(s_dataBuffer, s_data);
    }

    sprintf(buffer, "Device:\n{\nName: %s\nBattery: %s%%\nSignal Strength: %s%%\nStatus: %s\nDataBuffer: %s\n}\n", device->name, s_battery, s_signalStrength, s_status, s_dataBuffer);
}


const char* MWDeviceGetName(MWDevice *device) {
    return device->name;
}

uint8_t MWDeviceGetBattery(MWDevice *device) {
    return device->battery;
}

uint8_t MWDeviceGetSignalStrength(MWDevice *device) {
    return device->signalStrength;
}

MWDeviceStatus MWDeviceGetStatus(MWDevice *device) {
    return device->status;
}

uint8_t* MWDeviceGetDataBuffer(MWDevice *device) {
    return device->dataBuffer;
}

uint8_t MWDeviceGetDataBufferSize(MWDevice *device) {
    return device->dataBufferSize;
}


void MWDeviceSetName(MWDevice *device, const char *name) {
    device->name = name;
}

void MWDeviceSetBattery(MWDevice *device, uint8_t battery) {
    device->battery = (battery > 100) ? 100 : battery;
}

void MWDeviceSetSignalStrength(MWDevice *device, uint8_t signalStrength) {
    device->signalStrength = (signalStrength > 100) ? 100 : signalStrength;
}

void MWDeviceSetStatus(MWDevice *device, MWDeviceStatus status) {
    device->status = IsMWDeviceStatus(status) ? status : kUnknown;
}

void MWDeviceSetDataBuffer(MWDevice *device, uint8_t *dataBuffer) {
    device->dataBuffer = dataBuffer;
}
