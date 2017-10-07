#include "../inc/MWLog.h"

uint8_t __isLogEnable = 0;
MWLogLevel __outputLevel[kAmountOfSubSystems];
MWLogFunction __logFunction = NULL;

const char* MWLogLevel2String(MWLogLevel level) {
    switch (level) {
        case kNone:
            return "NONE";
            break;
        case kInfo:
            return "INFO";
            break;
        case kDebug:
            return "DEBUG";
            break;
        case kWarning:
            return "WARNING";
            break;
        case kError:
            return "ERROR";
            break;
        case kCritical:
            return "CRITICAL";
            break;
        default:
            return "";
            break;
    }
}

void MWLogInit(MWLogFunction function) {
    if (function != NULL)
        __logFunction = function;

    for (int i = 0; i < kAmountOfSubSystems; i++) {
        __outputLevel[i] = kNone;
    }
}

void MWLog(MWLogSubSystem subsystem, MWLogLevel level, const char *message) {
    if (__logFunction == NULL) return;
    char output[2500];

    sprintf(output, "%s [%s|%s|%d] ", __TIME__, MWLogLevel2String(level), __FILE__, __LINE__);
    strcat(output, message);

    if (__outputLevel[subsystem] >= level && __outputLevel[subsystem] != kNone && __isLogEnable)
        __logFunction(output);
}

void MWLogSetOutputLevel(MWLogSubSystem subsystem, MWLogLevel level) {
    __outputLevel[subsystem] = level;
}

void MWLogGlobalOn() {
    __isLogEnable = 1;
}

void MWLogGlobalOff() {
    __isLogEnable = 0;
}

void MWLogVersion(MWFirmwareVersion *version) {
    if (__logFunction == NULL || !__isLogEnable) return;

    char message[50];
    sprintf(message, "Current Firmware Version: %d.%d.%d\n", version->major, version->minor, version->build);
    __logFunction(message);
}
