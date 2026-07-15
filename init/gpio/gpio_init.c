#include "gpio_init.h"

GPIO_Config_t usart2_tx = {
    .port = GPIOA,
    .pin = 2,
    .mode = GPIO_MODE_AF,
    .otype = GPIO_PUSH_PULL,
    .speed = GPIO_SPEED_HIGH,
    .pull = GPIO_NO_PULL,
    .alternate = GPIO_AF1
};

GPIO_Config_t usart2_rx = {
    .port = GPIOA,
    .pin = 3,
    .mode = GPIO_MODE_AF,
    .otype = GPIO_PUSH_PULL,
    .speed = GPIO_SPEED_HIGH,
    .pull = GPIO_NO_PULL,
    .alternate = GPIO_AF1
};

void gpio_init_all(void)
{
    gpio_init(&usart2_tx);
    gpio_init(&usart2_rx);
}
