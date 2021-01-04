#include "osSemaphore.h"

#include "osKernel.h"

#include "stm32l4xx.h"

void osSemaphoreInit(uint32_t *semaphore, uint32_t value) {
  *semaphore = value;
}

void osSemaphoreWait(uint32_t *semaphore) {
  while (*semaphore <= 0) {
    // This yield operation is required for a `cooperative semaphore`
    // If the 3 lines below are disabled we have a `spinlock semaphore`
    __disable_irq();
    osKernelYield();
    __enable_irq();
  }

  __disable_irq();
  *semaphore -= 1;
  __enable_irq();
}

void osSemaphoreSignal(uint32_t *semaphore) {
  __disable_irq();
  *semaphore += 1;
  __enable_irq();
}
