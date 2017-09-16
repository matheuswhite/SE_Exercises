#ifndef MWDEVICE_H
#define MWDEVICE_H

#include "MWCommon.h"
#include "MWLog.h"

typedef void (*MWPrint)(const char*);

typedef enum {
    kDesconnected = 0,
    kConnected,
    kUnknown
} MWDeviceStatus;

typedef struct {
    const char *name;
    uint8_t battery;
    uint8_t signalStrength;
    MWDeviceStatus status;
    uint8_t *dataBuffer;
    uint8_t dataBufferSize;
} MWDevice;

#define DATABUFFERMAXSIZE 256

#define IsMWDeviceStatus(status) ((status) == kDesconnected || (status) == kConnected || (status) == kUnknown)

#define MWDeviceInit(_name, _battery, _signalStrength, _status, _dataBuffer) MWDevice _##_name;\
                                                                        _##_name.name = #_name;\
                                                                        if (_battery > 100) {\
                                                                            MWLog(kDevice, kWarning, "Battery level greater than 100%%\nSetting battery level to 100%%");\
                                                                            _##_name.battery = 100;\
                                                                        }\
                                                                        else {\
                                                                            _##_name.battery = _battery;\
                                                                        }\
                                                                        if (_signalStrength > 100) {\
                                                                            MWLog(kDevice, kWarning, "Signal strength level greater than 100%%\nSetting signal strength level to 100%%");\
                                                                            _##_name.signalStrength = 100;\
                                                                        }\
                                                                        else {\
                                                                            _##_name.signalStrength = _signalStrength;\
                                                                        }\
                                                                        _##_name.status = IsMWDeviceStatus(_status) ? (_status) : kUnknown;\
                                                                        _##_name.dataBuffer = (_dataBuffer);\
                                                                        _##_name.dataBufferSize = sizeof(_dataBuffer);\
                                                                        MWLog(kDevice, kInfo, "Use _<Device name> to acess the device created!");

void MWDeviceCopy(MWDevice *dst, MWDevice *src);
void MWDeviceShow(MWDevice *device, MWPrint function);
void MWDevice2String(MWDevice *device, char *buffer);

const char* MWDeviceGetName(MWDevice *device);
uint8_t MWDeviceGetBattery(MWDevice *device);
uint8_t MWDeviceGetSignalStrength(MWDevice *device);
MWDeviceStatus MWDeviceGetStatus(MWDevice *device);
uint8_t* MWDeviceGetDataBuffer(MWDevice *device);
uint8_t MWDeviceGetDataBufferSize(MWDevice *device);

void MWDeviceSetName(MWDevice *device, const char *name);
void MWDeviceSetBattery(MWDevice *device, uint8_t battery);
void MWDeviceSetSignalStrength(MWDevice *device, uint8_t signalStrength);
void MWDeviceSetStatus(MWDevice *device, MWDeviceStatus status);
void MWDeviceSetDataBuffer(MWDevice *device, uint8_t *dataBuffer);

#endif //MWDEVICE_H
