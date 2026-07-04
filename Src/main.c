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

int main(void)
{
	system_init();

	LED_t *pwm_led = get_pwm_led();
	LED_t *board_led = get_board_led();

	uint32_t last_breath_time = 0;
	uint32_t last_heartbeat_time = 0;

	int brightness = 0;
	int direction = 1;

	while (1)
	{
		uint32_t now = millis();
		if ((now - last_breath_time) >= BREATH_INTERVAL_MS)
		{
			last_breath_time = now;

			led_set_brightness(pwm_led, brightness);

			brightness += direction;

			if (brightness >= 100)
			{
				brightness = 100;
				direction = -1;
			}
			else if (brightness <= 0)
			{
				brightness = 0;
				direction = 1;
			}
		}

		if ((now - last_heartbeat_time) >= HEARTBEAT_INTERVAL_MS)
		{
			last_heartbeat_time = now;
			led_toggle(board_led);
		}
	}
}
