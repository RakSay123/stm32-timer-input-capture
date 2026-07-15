#include "uart_init.h"

#define FCLK 16000000
#define BAUD_RATE 115200

static UART_Config_t uartx_cfg = {
	.USARTx = USART2,
	.fclk = FCLK,
	.baud_rate = BAUD_RATE
};

void uart_init_all(void)
{
	uart_init(&uartx_cfg);
}
