#include "systick_init.h"

#define SYSTICK_1MS_TICKS (16000000 / 1000)

void systick_init_all(void)
{
	systick_init(SYSTICK_1MS_TICKS);
}
