#include "../inc/MWInvoker.h"

uint8_t MWInvokerRun(MWCommand invoker[]) {
    char input[MAX_INPUT];
    MWCommandName commandName;

    while(1)
        printf("blinkLED: %x\n", invoker[kBlinkLED].parameters[0].param);
        /*
    printf(">> ");
    readUARTString(input);
    commandName = MWString2CommandName(input);
    printf("Pass:%d\n", __LINE__);

    if (commandName != kUnknow) {
        for (uint8_t i = 0; i < invoker[commandName].amountOfParameters; i++) {
            if (invoker[commandName].parameters[i].parameterName == NULL)
                printf("Pass:%d\n", __LINE__);
            printf("Pass:%d\n", __LINE__);
            printf("%s: ", invoker[commandName].parameters[i].parameterName);
            printf("Pass:%d\n", __LINE__);
            readUARTString(input);
            invoker[commandName].parameters[i].param = atoi(input);
        }

        invoker[commandName].receiver(invoker[commandName].parameters);
    }
    else {
        {printf("Please enter one of the commands below or Ctrl+C to exit\n\n");}
        for (uint8_t i = 0; i < kAmountOfCommands; i++) {
            {printf("%s - %s\n", MWCommandName2String((MWCommandName)i), invoker[i].help);}
        }
    }
    */
    return 1;
}
