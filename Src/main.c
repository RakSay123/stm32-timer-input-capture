#include <stdint.h>
#include "stm32g070xx.h"
#include "device_instances.h"
#include "system/system.h"
#include "systick/systick.h"
#include "timer/timer.h"
#include "timer/timer_pwm/timer_pwm.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define BREATH_INTERVAL_MS 15
#define HEARTBEAT_INTERVAL_MS 300
#define SERVO_TICK_MS 2000
#define HALF_CYCLE_SWEEPS 12

int main(void)
{
	system_init();

	LED_t *pwm_led = get_pwm_led();
	LED_t *board_led = get_board_led();
	SERVO_t *mg90s = get_mg90s();

	uint32_t last_breath_time = 0;
	uint32_t last_heartbeat_time = 0;
	uint32_t last_servo_tick = 0;

	int brightness = 0;
	int led_direction = 1;

	int servo_angle = mg90s->min_angle;
	int servo_direction = (mg90s->max_angle - mg90s->min_angle) / HALF_CYCLE_SWEEPS;
	servo_set_min_angle(mg90s);
	systick_delay_s(5);

	while (1)
	{
		uint32_t now = millis();
		if ((now - last_breath_time) >= BREATH_INTERVAL_MS)
		{
			last_breath_time = now;

			led_set_brightness(pwm_led, brightness);

			brightness += led_direction;

			if (brightness >= 100)
			{
				brightness = 100;
				led_direction = -1;
			}
			else if (brightness <= 0)
			{
				brightness = 0;
				led_direction = 1;
			}
		}

		if ((now - last_heartbeat_time) >= HEARTBEAT_INTERVAL_MS)
		{
			last_heartbeat_time = now;
			led_toggle(board_led);
		}

		if ((now - last_servo_tick) >= SERVO_TICK_MS)
		{
			last_servo_tick = now;

			servo_set_angle(mg90s, servo_angle);

			servo_angle+=servo_direction;

			if (servo_angle >= mg90s->max_angle)
			{
				servo_angle = mg90s->max_angle;
				servo_direction = -servo_direction;
			}
			else if (servo_angle <= mg90s->min_angle)
			{
				servo_angle = mg90s->min_angle;
				servo_direction = -servo_direction;
			}
		}
	}
}
