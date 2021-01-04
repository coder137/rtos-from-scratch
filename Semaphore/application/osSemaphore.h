#ifndef OS_SEMAPHORE_H_
#define OS_SEMAPHORE_H_

#include <stdint.h>

void osSemaphoreInit(uint32_t *semaphore, uint32_t value);

void osSemaphoreWait(uint32_t *semaphore);
void osSemaphoreSignal(uint32_t *semaphore);

#endif
