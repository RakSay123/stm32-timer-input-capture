#include "device_instances.h"

static TIM_PWM_Config_t pwm_led_cfg = {
    .TIMx = TIM3,
    .channel = 1,
    .duty_cycle = 0,
    .pwm_mode = TIM_PWM1
};

static LED_t pwm_led = {
    .port = GPIOA,
    .pin = 6,
    .mode = LED_MODE_PWM,
	.alternate = GPIO_AF1,
    .pwm_cfg = &pwm_led_cfg
};

static LED_t board_led = {
    .port = GPIOA,
    .pin = 5,
    .mode = LED_MODE_GPIO,
	.alternate = GPIO_AF0
};

static TIM_PWM_Config_t mg90s_pwm_config = {
	.TIMx = TIM16,
	.channel = 1,
	.duty_cycle = 0,
	.pwm_mode = TIM_PWM1
};

static SERVO_t mg90s = {
	.port = GPIOB,
	.pin = 8,
	.alternate = GPIO_AF2,

	.pwm_cfg = &mg90s_pwm_config,

	.min_pulse_us = 1000,
	.max_pulse_us = 2000,

	.min_angle = -45,
	.max_angle = 45
};

LED_t* get_pwm_led(void)
{
	return &pwm_led;
}

LED_t* get_board_led(void)
{
	return &board_led;
}

SERVO_t* get_mg90s(void)
{
	return &mg90s;
}
