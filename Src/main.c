#include <stdint.h>
#include "stm32g070xx.h"
#include "system/system.h"
#include "device_instances.h"

#include "led/led.h"
#include "systick/systick.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{
	system_init();
	LED_t *led1 = get_led1();

	while (1)
	{
		led_toggle(led1);
		systick_delay_ms(500);
	}
}
