#ifndef MWUART_H
#define MWUART_H

#include "MWCommon.h"
#include "esp/uart.h"
#include "espressif/esp_common.h"

static void readUARTString(char *buffer) {
    uint8_t index = 0;
    int input;

    buffer[0] = '\0';
    while (index < 255) {
        input = uart_getc(0);
        uart_putc(0, input);

        if (input == '\r') {
            index = 0;
            break;
        }
        else {
            buffer[index] = input;
            buffer[index+1] = '\0';
            ++index;
        }
    }

    printf("\n");

    if (index > 255) {
        printf("[ERROR] Max size of input = 256\n");
    }
}

#endif
