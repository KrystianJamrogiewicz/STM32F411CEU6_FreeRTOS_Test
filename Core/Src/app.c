// ==============================================================================
// === APP IMPLEMENTATION =======================================================
// ==============================================================================

#include "app.h"
#include <string.h> // Needed for strlen()


// ==========================================
// TASK: LED blinking
// ==========================================

void vLEDTask(void *argument)
{
	// INITIALIZATION (Performed ONLY ONCE)
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	osDelay(3000); // RTOS: Sleep this thread for 3000 ms

	// TASK LOOP (Infinite)
    for(;;)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        osDelay(500); // RTOS: Sleep this thread for 500 ms
    }

    // WARNING: The code must never reach this point!
    // If the task jumps out of the for(;;) loop, FreeRTOS will crash (HardFault).
}


// ==========================================
// TASK: UART communication
// ==========================================
void vUARTTask(void *argument)
{
    char msg[] = "RTOS UART\r\n";

    for(;;)
    {
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
        osDelay(2000);
    }
}
