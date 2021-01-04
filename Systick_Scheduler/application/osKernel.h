#ifndef OS_KERNEL_H_
#define OS_KERNEL_H_

#include <stdint.h>

uint8_t osKernelAddThreads(void (*thread0)(void), void (*thread1)(void),
                           void (*thread2)(void));

void osKernelLaunch(uint32_t quanta);

// For cooperative scheduling
// Raise an interrupt to the SysTick Handler
void osKernelYield(void);

#endif
