#ifndef MWINVOKER_H
#define MWINVOKER_H

#include "MWCommand.h"

typedef MWCommand* MWInvoker;

#define MAX_PARAMS 4
#define MAX_INPUT  256

#define MWInvokerCreate(...)\
            MWCommand invoker[kAmountOfCommands] = { __VA_ARGS__ }

uint8_t MWInvokerRun(MWInvoker invoker);

#endif
