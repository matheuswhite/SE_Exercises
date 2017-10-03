#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "esp8266.h"
#include "esp/uart.h"
#include "espressif/esp_common.h"
#include "inc/MWInvoker.h"

//Defines
#define BUTTON_GPIO 5
#define BUTTON_ACTIVE 0
#define LED_GPIO 2
#define HIGH 0
#define LOW  1

//Variables
static uint8_t blinkLEDFrequency = 1;
static uint8_t buttonConfigStatus = 0;
static uint8_t isBlinkLEDEnable = 1;
static uint8_t ledStatus = LOW;
static MWCommand invoker[kAmountOfCommands];

//Tasks
void blinkLEDTask(void *pvParameters) {
    while(1) {
        gpio_write(LED_GPIO, ledStatus);
        vTaskDelay((1000/blinkLEDFrequency) / portTICK_PERIOD_MS);
        if (isBlinkLEDEnable)
            ledStatus = !ledStatus;
    }
}

void runInvokerTask(void *pvParameters) {
    while (1) {
        MWInvokerRun(invoker);
    }
}

void listenButtonTask(void *pvParameters) {
    while(1) {
        while(gpio_read(BUTTON_GPIO) != BUTTON_ACTIVE)
        {
            isBlinkLEDEnable = !buttonConfigStatus;
            taskYIELD();
        }
        isBlinkLEDEnable = buttonConfigStatus;
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

//receiver functions
void blinkLED(MWParameter arg) {
    blinkLEDFrequency = arg.param;
    printf("Blinking LED at %dHz\n", arg.param);
}

void buttonConfig(MWParameter arg) {
    buttonConfigStatus = arg.param;
    printf("The button %s the blink LED\n", (arg.param == 0) ? "disable" : "enable");
}

void showVersion(MWParameter arg) {
    printf("%d.%d.%d\n", MAJOR, MINOR, BUILD);
}

//main function
void user_init(void)
{
    uart_set_baud(0, 115200);
    {printf("SDK version:%s\n", sdk_system_get_sdk_version());}
    //gpio config
    gpio_enable(BUTTON_GPIO, GPIO_INPUT);
    gpio_enable(LED_GPIO, GPIO_OUTPUT);

    //invoker config
    MWParameter blinkLEDParameter;
    MWParameter buttonConfigParameter;
    MWParameter showVersionParameter;

    MWParameterCreate(&blinkLEDParameter, "Frequency");
    MWParameterCreate(&buttonConfigParameter, "Action");
    MWParameterCreate(&showVersionParameter, "");

    MWCommandCreate(&invoker[kBlinkLED], kBlinkLED, blinkLED, "Sets how often the LED will blink", blinkLEDParameter);
    MWCommandCreate(&invoker[kButtonConfig], kButtonConfig, buttonConfig, "Sets whether the button will enable or disable the blink LED", buttonConfigParameter);
    MWCommandCreate(&invoker[kShowVersion], kShowVersion, showVersion, "Shows the version of current firmware", showVersionParameter);

    //start tasks
    xTaskCreate(blinkLEDTask, "blinkLEDTask", 256, NULL, 2, NULL);
    xTaskCreate(runInvokerTask, "runInvokerTask", 256, NULL, 2, NULL);
    xTaskCreate(listenButtonTask, "listenButtonTask", 256, NULL, 2, NULL);
}
