#include "esp/uart.h"
#include "espressif/esp_common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "esp8266.h"
#include "inc/MWInvoker.h"

//Defines
#define BUTTON_GPIO 13
#define BUTTON_ACTIVE 0
#define LED_GPIO 2

//Variables
static uint8_t blinkLEDFrequency = 1;
static uint8_t buttonConfigStatus = 0;
static uint8_t isBlinkLEDEnable = 1;
static MWCommand *_invoker = NULL;

//Tasks
void blinkLEDTask(void *pvParameters) {
    while(1) {
        if (isBlinkLEDEnable) {
            gpio_write(LED_GPIO, 1);
            vTaskDelay((1000/blinkLEDFrequency) / portTICK_PERIOD_MS);
            gpio_write(LED_GPIO, 0);
            vTaskDelay((1000/blinkLEDFrequency) / portTICK_PERIOD_MS);
        }
        else {
            gpio_write(LED_GPIO, 0);
        }
    }
}

void runInvokerTask(void *pvParameters) {
    while (MWInvokerRun(_invoker));
}

void listenButtonTask(void *pvParameters) {
    while(1) {
        while(gpio_read(BUTTON_GPIO) != BUTTON_ACTIVE)
        {
            isBlinkLEDEnable = ~buttonConfigStatus;
            taskYIELD();
        }
        isBlinkLEDEnable = buttonConfigStatus;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

//receiver functions
void blinkLED(MWParameter *args) {
    blinkLEDFrequency = args[0].param;
    printf("Blinking LED at %dHz\n", args[0].param);
}

void buttonConfig(MWParameter *args) {
    buttonConfigStatus = args[0].param;
    printf("The button %s the blink LED\n", (args[0].param == 0) ? "disable" : "enable");
}

void showVersion(MWParameter *args) {
    printf("%d.%d.%d\n", MAJOR, MINOR, BUILD);
}

//main function
void user_init(void)
{
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());

    //gpio config
    gpio_enable(BUTTON_GPIO, GPIO_INPUT);
    gpio_enable(LED_GPIO, GPIO_OUTPUT);

    //invoker config
    MWParameter blinkLEDParameters[1] = MWParameterCreate("Frequency");
    MWParameter buttonConfigParameters[1] = MWParameterCreate("Action");
    MWParameter showVersionParameters[1] = MWParameterNone();

    MWInvokerCreate(MWCommandCreate(kBlinkLED, blinkLED, "Sets how often the LED will blink", blinkLEDParameters),
                    MWCommandCreate(kButtonConfig, buttonConfig, "Sets whether the button will enable or disable the blink LED", buttonConfigParameters),
                    MWCommandCreate(kShowVersion, showVersion, "Shows the version of current firmware", showVersionParameters));
    _invoker = invoker;

    //start tasks
    xTaskCreate(blinkLEDTask, "blinkLEDTask", 256, NULL, 2, NULL);
    xTaskCreate(runInvokerTask, "runInvokerTask", 256, NULL, 3, NULL);
    xTaskCreate(listenButtonTask, "listenButtonTask", 256, NULL, 4, NULL);
}
