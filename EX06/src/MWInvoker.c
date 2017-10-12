#include "../inc/MWInvoker.h"

uint8_t MWInvokerRun(MWCommand invoker[]) {
    char input[MAX_INPUT];
    MWCommandName commandName;

    printf(">> ");
    readUARTString(input);
    commandName = MWString2CommandName(input);

    if (commandName != kUnknow) {
        if (strcmp(invoker[commandName].parameter.parameterName, "") != 0) {
            printf("%s: ", invoker[commandName].parameter.parameterName);
            readUARTString(input);
            invoker[commandName].parameter.param = atoi(input);
        }

        invoker[commandName].receiver(invoker[commandName].parameter);
    }
    else {
        {printf("Please enter one of the commands below or Ctrl+C to exit\n\n");}
        for (uint8_t i = 0; i < kAmountOfCommands; i++) {
            {printf("%s - %s\n", MWCommandName2String((MWCommandName)i), invoker[i].help);}
        }
    }

    return 1;
}
