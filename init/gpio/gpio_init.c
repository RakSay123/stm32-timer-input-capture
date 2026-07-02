#include "gpio_init.h"

static GPIO_Config_t PA6 = {
	.port = GPIOA,
	.pin = 6,
	.mode = GPIO_MODE_AF,
	.otype = GPIO_PUSH_PULL,
	.speed = GPIO_SPEED_HIGH,
	.pull = GPIO_NO_PULL,
	.alternate = GPIO_AF1
};

void gpio_init_all(void)
{
//	gpio_init(&PA6);
}
