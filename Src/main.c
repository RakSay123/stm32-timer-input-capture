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

#define DELAY_MS 15

int main(void)
{
	system_init();

	LED_t *led = get_pwm_led();
	led_set_brightness(led, 0);

	while (1)
	{
		for (int brightness = 0; brightness < 100; brightness++)
		{
			led_set_brightness(led, brightness);
			systick_delay_ms(DELAY_MS);
		}

		for (int brightness = 100; brightness > 0; brightness--)
		{
			led_set_brightness(led, brightness);
			systick_delay_ms(DELAY_MS);
		}
	}
}
