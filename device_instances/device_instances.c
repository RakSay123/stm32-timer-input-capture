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

static TIM_Input_Capture_Config_t pwm_monitor_tim_ic_cfg = {
    .TIMx = TIM16,
    .channel = 1,
    .input_selection = TIM_IC_INPUT_DIRECT,
    .psc = TIM_IC_PSC_NONE,
    .filter = TIM_IC_FILTER_NONE,
    .mode = TIM_IC_EDGE_BOTH
};

static PWM_Monitor_t pwm_monitor = {
    .port = GPIOD,
    .pin = 0,
    .alternate = GPIO_AF2,

	.capture_cfg = &pwm_monitor_tim_ic_cfg,
	.USARTx = USART2,

	.state = PWM_MONITOR_WAIT_RISING,

	.rising_timestamp = 0,
	.falling_timestamp = 0,
	.next_rising_timestamp = 0,

	.period_ticks = 0,
	.high_ticks = 0,
	.low_ticks = 0,
	.duty_percent = 0
};

LED_t* get_pwm_led(void)
{
	return &pwm_led;
}

LED_t* get_board_led(void)
{
	return &board_led;
}

PWM_Monitor_t* get_pwm_monitor(void)
{
	return &pwm_monitor;
}
