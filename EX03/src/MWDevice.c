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
    if (dst == NULL) {
        MWLog(kDevice, kError, "Device dst equal to NULL");
        return;
    }
    if (src == NULL) {
        MWLog(kDevice, kError, "Device src equal to NULL");
        return;
    }

    MWLog(kDevice, kDebug, "Copying device \"dst\" to device \"src\"");
    dst->name = src->name;
    dst->battery = src->battery;
    dst->signalStrength = src->signalStrength;
    dst->status = src->status;
    dst->dataBuffer = src->dataBuffer;
}

void MWDeviceShow(MWDevice *device, MWPrint function) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    char buffer[2048];
    MWDevice2String(device, buffer);
    function(buffer);
}

void MWDevice2String(MWDevice *device, char *buffer) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

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
    s_dataBuffer[0] = '\0';
    for (i = 0; i < device->dataBufferSize; ++i) {
        s_data[0] = '\0';
        sprintf(s_data, "0x%x, ", device->dataBuffer[i]);
        strcat(s_dataBuffer, s_data);
    }

    sprintf(buffer, "Device:\n{\nName: %s\nBattery: %s%%\nSignal Strength: %s%%\nStatus: %s\nDataBuffer: %s\n}\n", device->name, s_battery, s_signalStrength, s_status, s_dataBuffer);
}


const char* MWDeviceGetName(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return NULL;
    }

    return device->name;
}

uint8_t MWDeviceGetBattery(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return -1;
    }

    return device->battery;
}

uint8_t MWDeviceGetSignalStrength(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return -1;
    }

    return device->signalStrength;
}

MWDeviceStatus MWDeviceGetStatus(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return kUnknown;
    }

    return device->status;
}

uint8_t* MWDeviceGetDataBuffer(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return NULL;
    }

    return device->dataBuffer;
}

uint8_t MWDeviceGetDataBufferSize(MWDevice *device) {
    if (device == NULL) {
        MWLog(kDevice, kCritical, "Device equal to NULL");
        return -1;
    }

    return device->dataBufferSize;
}


void MWDeviceSetName(MWDevice *device, const char *name) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    device->name = name;
}

void MWDeviceSetBattery(MWDevice *device, uint8_t battery) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    if (battery > 100) {
        MWLog(kDevice, kWarning, "Battery level greater than 100%%\nSetting battery level to 100%%");\
        device->battery = 100;
    }
    else {
        device->battery = battery;
    }
}

void MWDeviceSetSignalStrength(MWDevice *device, uint8_t signalStrength) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    if (signalStrength > 100) {
        MWLog(kDevice, kWarning, "Signal strength level greater than 100%%\nSetting signal strength level to 100%%");
        device->signalStrength = 100;
    }
    else {
        device->signalStrength = signalStrength;
    }
}

void MWDeviceSetStatus(MWDevice *device, MWDeviceStatus status) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    device->status = IsMWDeviceStatus(status) ? status : kUnknown;
}

void MWDeviceSetDataBuffer(MWDevice *device, uint8_t *dataBuffer) {
    if (device == NULL) {
        MWLog(kDevice, kError, "Device equal to NULL");
        return;
    }

    device->dataBuffer = dataBuffer;
}
