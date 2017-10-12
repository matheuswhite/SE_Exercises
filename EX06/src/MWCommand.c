#include "../inc/MWCommand.h"

void MWParameterCreate(MWParameter *parameter, const char *parameterName) {
    parameter->parameterName = parameterName;
    parameter->param = 0x00;
}

void MWCommandCreate(MWCommand *command, MWCommandName name, MWReceiver receiver,
                        const char *help, MWParameter parameter) {
    command->name = name;
    command->receiver = receiver;
    command->help = help;
    command->parameter = parameter;
}

MWCommandName MWString2CommandName(const char *name) {
    if (strcmp(name, "BlinkLED") == 0) {
        return kBlinkLED;
    }
    else if (strcmp(name, "ButtonConfig") == 0) {
        return kButtonConfig;
    }
    else if (strcmp(name, "ShowVersion") == 0) {
        return kShowVersion;
    }
    else {
        return kUnknow;
    }
}

const char* MWCommandName2String(MWCommandName commandName) {
    switch (commandName) {
        case kBlinkLED:
            return "BlinkLED";
            break;
        case kButtonConfig:
            return "ButtonConfig";
            break;
        case kShowVersion:
            return "ShowVersion";
            break;
        default:
            return "Unknow";
            break;
    }
}
