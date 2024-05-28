#include "bsp_systick.h"

void bsp_systick_init()
{
	;
	//Systick用于给FreeRTOS提供时钟
	// 在vTaskStartScheduler() -> xPortStartScheduler() -> vPortSetupTimerInterrupt() 中会按照FreeRTOSConfig中配置时钟配置systick。
}
