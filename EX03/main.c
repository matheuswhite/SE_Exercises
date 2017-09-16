#include "inc/MWDevice.h"
#include "inc/MWLog.h"

void print(const char *str) {
    printf("%s\n", str);
}

int main(int argc, char const *argv[]) {
    uint8_t data[] = {0x0, 0x1, 0x2, 0xa, 0xf};
    uint8_t data2[] = {0x9, 0x7, 0xc, 0x30, 0xd};
    uint8_t data3[] = {0x23, 0x8, 0xe, 0x5a, 0x81};
    MWFirmwareVerision version = {MAJOR, MINOR, BUILD};

    MWLogInit(print);
    MWDeviceInit(device1, 80, 43, kConnected, data);
    MWDeviceInit(device2, 90, 87, kDesconnected, data2);

    MWLogGlobalOn();
    MWLogSetOutputLevel(kDevice, kCritical);

    MWLogVersion(&version);

    MWDeviceSetName(&_device1, "Device1");
    MWDeviceSetBattery(&_device1, 110);
    MWDeviceSetDataBuffer(&_device1, data2);
    MWDeviceSetStatus(&_device1, kDesconnected);
    MWDeviceSetSignalStrength(&_device1, 80);
    MWDeviceShow(&_device1, print);

    MWDeviceSetName(&_device2, "Device2");
    MWDeviceSetBattery(NULL, 47);
    MWDeviceSetDataBuffer(&_device2, data3);
    MWDeviceSetStatus(&_device2, kUnknown);
    MWDeviceSetSignalStrength(&_device2, 200);
    MWDeviceShow(&_device2, print);

    MWDeviceCopy(&_device2, &_device1);

    return 0;
}
