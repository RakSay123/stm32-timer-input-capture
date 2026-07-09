#include "timer_init.h"

static TIM_Config_t tim3_cfg = {
	.TIMx = TIM3,
	.psc = 16 - 1,
	.arr = 1000 - 1,
	.cnt = 0,
	.interrupt_status = TIM_INTERRUPTS_DISABLED
};

static TIM_Config_t tim16_cfg = {
	.TIMx = TIM16,
	.psc = 16 - 1,
	.arr = 20000 - 1,
	.cnt = 0,
	.interrupt_status = TIM_INTERRUPTS_DISABLED
};

void timer_init_all(void)
{
	timer_init(&tim3_cfg);
	timer_init(&tim16_cfg);
}
