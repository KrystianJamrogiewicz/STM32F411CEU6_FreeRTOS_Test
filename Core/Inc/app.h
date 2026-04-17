// ==============================================================================
// === APP LIBRARY ==============================================================
// ==============================================================================

// Double inclusion prevention
#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"
#include "cmsis_os.h" // Necessary for RTOS functions (e.g. osDelay)

// --- C++ Compatibility ---
// Allows this C code to be safely used in C++ projects (prevents name mangling)
#ifdef __cplusplus
extern "C" {
#endif


extern UART_HandleTypeDef huart1; // Link to the hardware UART1 configuration.


// Prototypes of FreeRTOS tasks

/* * IMPORTANT: To avoid "multiple definition" linker errors, ensure that
 * the auto-generated empty task functions at the bottom of main.c are deleted */

// Name "vLEDTask" is in: .ico / Middlewares and Software Packs / FREERTOS / Tasks and Queues /
// / "Edit Task / Entry Function"

/* *argument - Generic pointer used to pass parameters (e.g., pin number) during task creation. */
/* It allows reusing a single task function for multiple independent instances. */
void vLEDTask(void *argument);
void vUARTTask(void *argument);


// --- C++ Compatibility (Closing) ---
#ifdef __cplusplus
}
#endif


#endif
