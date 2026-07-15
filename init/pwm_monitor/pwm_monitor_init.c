#include "pwm_monitor_init.h"

void pwm_monitor_init_all(void)
{
    pwm_monitor_init(get_pwm_monitor());
}