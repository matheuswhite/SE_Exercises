#include "inc/MWInvoker.h"

void blinkLED(MWParameter *args) {
    printf("Blinking LED at %dHz\n", args[0].param);
}

void buttonConfig(MWParameter *args) {
    printf("The button %s the blink LED\n", (args[0].param == 0) ? "disable" : "enable");
}

void showVersion(MWParameter *args) {
    printf("%d.%d.%d\n", MAJOR, MINOR, BUILD);
}

int main() {

    MWParameter blinkLEDParameters[1] = MWParameterCreate("Frequency");
    MWParameter buttonConfigParameters[1] = MWParameterCreate("Action");
    MWParameter showVersionParameters[1] = MWParameterNone();

    MWInvokerCreate(MWCommandCreate(kBlinkLED, blinkLED, "Sets how often the LED will blink", blinkLEDParameters),
                    MWCommandCreate(kButtonConfig, buttonConfig, "Sets whether the button will enable or disable the blink LED", buttonConfigParameters),
                    MWCommandCreate(kShowVersion, showVersion, "Shows the version of current firmware", showVersionParameters));

    printf("Program %s in execution.\n", __FILE__);
    while (MWInvokerRun(invoker));

    return 0;
}
