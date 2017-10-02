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

void MWParameterCreate(MWParameter *parameter, const char *parameterName);
void MWCommandCreate(MWCommand *command, MWCommandName name, MWReceiver receiver,
                        const char *help, MWParameter *parameters, uint8_t amountOfParameters);

MWCommandName MWString2CommandName(const char *name);
const char* MWCommandName2String(MWCommandName commandName);

#endif
