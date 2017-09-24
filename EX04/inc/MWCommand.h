#ifndef MWCOMMAND_H
#define MWCOMMAND_H

#include "MWCommon.h"

typedef enum {
    kBlinkLED,
    kButtonConfig,
    kShowVersion,
    kAmountOfCommands,
    kUnknow
} MWCommandName;

typedef struct {
    const char *parameterName;
    uint8_t param;
} MWParameter;

typedef void (*MWReceiver)(MWParameter*);

typedef struct {
    MWCommandName name;
    MWReceiver receiver;
    const char *help;
    MWParameter *parameters;
    uint8_t amountOfParameters;
} MWCommand;

#define MWParameterCreate(parameterName) {parameterName, 00}
#define MWParameterNone() {"", 00}
#define MWCommandCreate(name, receiver, help, parameters) {name, receiver, help, parameters, strcmp(parameters[0].parameterName, "") == 0 ? 0 : sizeof(parameters)/sizeof(MWParameter)}

MWCommandName MWString2CommandName(const char *name);
const char* MWCommandName2String(MWCommandName commandName);

#endif
