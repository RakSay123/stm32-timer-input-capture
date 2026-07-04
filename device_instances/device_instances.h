#pragma once

#include "stm32g070xx.h"
#include "led/led.h"

LED_t* get_pwm_led(void);

LED_t* get_board_led(void);
