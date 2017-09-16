#include "inc/MWDevice.h"

void print(const char *str) {
    printf("%s\n", str);
}

int main(int argc, char const *argv[]) {
    uint8_t data[] = {0x0, 0x1, 0x2, 0xa, 0xf};
    uint8_t data2[] = {0x9, 0x7, 0xc, 0x30, 0xd};
    uint8_t data3[] = {0x23, 0x8, 0xe, 0x5a, 0x81};
    char buffer1[2048];
    char buffer2[2048];

    printf("Current firmware version %d.%d.%d\n\n", MAJOR, MINOR, BUILD);

    MWDeviceInit(device1, 100, 110, kConnected, data);
    MWDeviceInit(device2, 200, 95, kDesconnected, data2);

    MWDeviceShow(&_device1, print);
    MWDeviceShow(&_device2, print);

    MWDeviceSetName(&_device1, "Device1");
    MWDeviceSetBattery(&_device1, 75);
    MWDeviceSetDataBuffer(&_device1, data2);
    MWDeviceSetStatus(&_device1, kDesconnected);
    MWDeviceSetSignalStrength(&_device1, 80);
    MWDeviceShow(&_device1, print);

    MWDeviceSetName(&_device2, "Device2");
    MWDeviceSetBattery(&_device2, 47);
    MWDeviceSetDataBuffer(&_device2, data3);
    MWDeviceSetStatus(&_device2, kUnknown);
    MWDeviceSetSignalStrength(&_device2, 15);
    MWDeviceShow(&_device2, print);

    MWDeviceCopy(&_device2, &_device1);

    MWDevice2String(&_device1, buffer1);
    MWDevice2String(&_device2, buffer2);
    printf("%s\n", buffer1);
    printf("%s\n", buffer2);

    return 0;
}
