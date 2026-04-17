# STM32F411CEU6_FreeRTOS_Test


### Setting up FreeRTOS in STM32CubeIDE
After creating the project and configuring the basic hardware (e.g., GPIO for the LED and USART1 for communication).

#### Step 1: The Most Important RTOS Step (Timebase Source)
FreeRTOS needs to know how much time passes to effectively switch between tasks. It uses the main CPU timer, called `SysTick`. Because of this, we must take the SysTick timer away from the HAL library and assign it to FreeRTOS.

1. In the left menu, go to **System Core -> SYS**.
2. Find the **Timebase Source** field. Change it from `SysTick` to any other available hardware timer, for example, **TIM11**.
*(Note: If you skip this step, STM32CubeIDE will show a warning during code generation).*

![SYS Timebase Source configuration](docs/img/step_1.png)

#### Step 2: Enabling FreeRTOS & Thread Safety
1. From the left menu, select **Middleware and Software Packs -> FREERTOS**.
2. In the top window, under the *Interface* section, change the option from `Disable` to **CMSIS_V2** (the modern, recommended standard for new projects).
3. **Crucial Setting:** Go to the **Advanced Settings** tab. Find the **USE_NEWLIB_REENTRANT** option and set it to **Enabled**. 
*(Why? This allocates separate memory areas for each task, ensuring that standard C library functions—like `strlen` or `sprintf`—do not crash the system when multiple tasks try to use them at the same time).*

![Enabling FreeRTOS & Thread Safety](docs/img/step_2.png)

#### Step 3: Creating Tasks (Tasks and Queues)
Now we tell the operating system what it should run in parallel.

1. Scroll down in the FreeRTOS configuration window and select the **Tasks and Queues** tab.
2. You will see an existing default task named `defaultTask`. Double-click it.
3. Change its **Task Name** to `LED` and change its **Entry Function** to `vLEDTask`.
4. Click the **Add** button to create a second task. Name it `UART` and set its **Entry Function** to `vUARTTask`.

![Creating Tasks (Tasks and Queues)](docs/img/step_3.png)

**Important Task Parameters Explained:**
* **Priority:** Leave both tasks at `osPriorityNormal`. In RTOS, a higher priority task will instantly interrupt a lower priority one. Since blinking an LED and sending standard UART messages are not time-critical, normal priority is perfect.
* **Stack Size:** We leave it at `128` (words). If your task processes large strings or complex math in the future, you might need to increase this (e.g., to `256` or `512`) to prevent a Stack Overflow.

#### Step 4: Code Generation & Clean Architecture
1. Click the gear icon on the top bar (or **Project -> Generate Code**) and save the `.ioc` file.
2. Open the generated `main.c` file. 

To keep the project modular, we do not write our code inside `main.c`. Instead:
1. Create `app.c` in the `Core/Src` folder and `app.h` in the `Core/Inc` folder.
2. Write your infinite task loops inside `void vLEDTask(void *argument)` and `void vUARTTask(void *argument)` inside `app.c`. 
3. Simply add `#include "app.h"` at the top of your `main.c` file.

#### Step 5: The "Multiple Definition" Cleanup Rule
Because we moved our task functions to a dedicated `app.c` file, we must manually manage the code generator. 

Every time you change something in the `.ioc` file and re-generate the code, STM32CubeIDE will automatically create empty templates for `vLEDTask` and `vUARTTask` at the very bottom of `main.c`. 

**You must manually delete these auto-generated empty functions from `main.c` after every build!** If you forget, the compiler will find two functions with the exact same name (one in `main.c` and one in `app.c`) and throw a `Multiple definition` linker error.

![The "Multiple Definition" Cleanup Rule](docs/img/step_5.png)

*(Pro-Tip: Once you are comfortable with this workflow, you can automate this. In the `.ioc` file, double-click your task and change the **Code Generation Option** from `Default` to `As external`. This tells the generator to stop creating those empty functions in main.c completely).*