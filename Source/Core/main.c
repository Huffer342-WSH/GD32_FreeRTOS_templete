#include "gd32f3x0.h"
#include "FreeRTOS.h"
#include "task.h"
#include "SEGGER_RTT.h"
#include "bsp_uart.h"

void vTask1(void *pvParameters);

void vTask2(void *pvParameters);

int main(void)
{
	SEGGER_RTT_Init();
	BSP_Uart_Init();

	SEGGER_RTT_WriteString(0, "Hello World\r\n");
	for (size_t i = 0; i < 5; i++) {
		UART_Transmit_DMA("Uart test\n", 10);
	}

	xTaskCreate(vTask1, "Task 1", 128, NULL, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 128, NULL, 2, NULL);

	vTaskStartScheduler();

	for (;;)
		;
}
void vTask1(void *pvParameters)
{
	char *task_name;
	TickType_t xLastWakeTime;

	task_name = pcTaskGetName(xTaskGetCurrentTaskHandle());
	uint32_t time = 0;
	xLastWakeTime = xTaskGetTickCount();

	SEGGER_RTT_printf(0, "%s start\n", task_name);
	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;) {
		/* Print out the name of this task. */
		vTaskDelayUntil(&xLastWakeTime, 1000);
		SEGGER_RTT_printf(0, "[%s]: %d s\n", task_name, time++);
	}
}

void vTask2(void *pvParameters)
{
	TickType_t xLastWakeTime;

	uint32_t time = 0;
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;) {
		/* Print out the name of this task. */
		vTaskDelayUntil(&xLastWakeTime, 1000);
		UART_Transmit_DMA("Uart test\n", 10);
	}
}
