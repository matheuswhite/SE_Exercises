#ifndef MWUART_H
#define MWUART_H

#include "MWCommon.h"
#include "esp/uart.h"
#include "espressif/esp_common.h"

static void readUARTString(char *buffer) {
    uint8_t index = 0;
    int input = '\n';

    while (index <= 255) {
        input = uart_getc(0);
        printf("Buffer: %s\n", buffer);

        if (input == '\n') {
            index = 0;
            break;
        }
        else {
            buffer[index] = input;
            ++index;
        }
    }
}

#endif
