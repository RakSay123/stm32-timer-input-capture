#pragma once

#include "stm32g070xx.h"
#include "led/led.h"
#include "servo/servo.h"

LED_t* get_pwm_led(void);

LED_t* get_board_led(void);

SERVO_t* get_mg90s(void);
