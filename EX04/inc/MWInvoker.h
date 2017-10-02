#ifndef MWINVOKER_H
#define MWINVOKER_H

#include "MWCommand.h"
#include "MWUART.h"

#define MAX_PARAMS 4
#define MAX_INPUT  256

uint8_t MWInvokerRun(MWCommand *invoker);

#endif
