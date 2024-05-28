#include "bsp_log.h"
#include "printf.h"
#include "SEGGER_RTT.h"
void _putchar(char character)
{
	SEGGER_RTT_Write(0, &character, 1);
}

void assert_failed(char *file, uint32_t line)
{
	LOG("Assert failed: file %s on line %d\r\n", file, line);
}
