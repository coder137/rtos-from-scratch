#include "osSemaphore.h"

#include "stm32l4xx.h"

void osSemaphoreInit(uint32_t *semaphore, uint32_t value) {
  *semaphore = value;
}

void osSemaphoreWait(uint32_t *semaphore) {
  while (*semaphore <= 0) {
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
