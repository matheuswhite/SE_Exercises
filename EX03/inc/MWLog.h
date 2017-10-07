#ifndef MWLOGGING_H
#define MWLOGGING_H

#include "MWCommon.h"

typedef void (*MWLogFunction)(const char*);

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} MWFirmwareVersion;

typedef enum {
    kDevice = 0,
    kAmountOfSubSystems
} MWLogSubSystem;

typedef enum {
    kNone = 0,
    kInfo,
    kDebug,
    kWarning,
    kError,
    kCritical
} MWLogLevel;

void MWLogInit(MWLogFunction function);
void MWLog(MWLogSubSystem subsystem, MWLogLevel level, const char *message);
void MWLogSetOutputLevel(MWLogSubSystem subsystem, MWLogLevel level);
void MWLogGlobalOn();
void MWLogGlobalOff();
void MWLogVersion(MWFirmwareVersion *version);

#endif /* end of include guard: MWLOGGING_H */
