#include "led_init.h"

void led_init_all()
{
	led_init(get_pwm_led());
	led_init(get_board_led());
}
