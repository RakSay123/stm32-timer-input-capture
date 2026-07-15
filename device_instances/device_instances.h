#pragma once

#include "stm32g070xx.h"
#include "led/led.h"
#include "pwm_monitor/pwm_monitor.h"

LED_t* get_pwm_led(void);

LED_t* get_board_led(void);

PWM_Monitor_t* get_pwm_monitor(void);

