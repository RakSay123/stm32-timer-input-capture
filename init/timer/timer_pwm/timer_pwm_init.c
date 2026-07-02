#include "timer_pwm_init.h"

TIM_PWM_Config_t pwm_led = {
    .TIMx = TIM3,
    .channel = 1,
    .duty_cycle = 50,
    .pwm_mode = TIM_PWM1
};

void timer_pwm_init_all()
{
	timer_pwm_init(&pwm_led);
}
