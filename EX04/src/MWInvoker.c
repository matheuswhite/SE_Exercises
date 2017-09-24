#include "../inc/MWInvoker.h"

uint8_t MWInvokerRun(MWInvoker invoker) {
    char input[MAX_INPUT];
    MWCommandName commandName;

    printf(">> ");
    scanf("%s", input);
    commandName = MWString2CommandName(input);

    if (commandName != kUnknow) {
        for (uint8_t i = 0; i < invoker[commandName].amountOfParameters; i++) {
            printf("%s: ", invoker[commandName].parameters[i].parameterName);
            scanf("%s", input);
            invoker[commandName].parameters[i].param = atoi(input);
        }

        invoker[commandName].receiver(invoker[commandName].parameters);
    }
    else {
        printf("Please enter one of the commands below or Ctrl+C to exit\n\n");
        for (uint8_t i = 0; i < kAmountOfCommands; i++) {
            printf("%s - %s\n", MWCommandName2String((MWCommandName)i), invoker[i].help);
        }
    }

    return 1;
}
