#include "led/led.h"

static LED_t LED1 = {
    .port = GPIOA,
    .pin = 5
};

LED_t* get_led1(void)
{
    return &LED1;
}
