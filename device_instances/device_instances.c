#include "led/led.h"

static TIM_PWM_Config_t pwm_led_cfg = {
    .TIMx = TIM3,
    .channel = 1,
    .duty_cycle = 50,
    .pwm_mode = TIM_PWM1
};

static LED_t pwm_led = {
    .port = GPIOA,
    .pin = 6,
    .mode = LED_MODE_PWM,
	.alternate = GPIO_AF1,
    .pwm_cfg = &pwm_led_cfg
};


LED_t* get_pwm_led(void)
{
	return &pwm_led;
}
