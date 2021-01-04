#include "osKernel.h"

#include "stm32l4xx.h"

// Constants
#define NUM_OF_THREADS 3
#define STACKSIZE 100
struct tcb {
  uint32_t *stackPt;
  struct tcb *nextPt;
};
typedef struct tcb tcbType;

// Static functions
static void osKernelStackInit(int thread_number);

// Calls the assembly function
extern void osSchedulerLaunch(void);

// State variables
static tcbType tcbs[NUM_OF_THREADS];
static uint32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

// * NOTE, Do not make this static since it is used by the osKernel.S file
tcbType *currentPt;

uint8_t osKernelAddThreads(void (*thread0)(void), void (*thread1)(void),
                           void (*thread2)(void)) {
  __disable_irq();

  // Create a Circular Linked list here
  tcbs[0].nextPt = &tcbs[1];
  tcbs[1].nextPt = &tcbs[2];
  tcbs[2].nextPt = &tcbs[0];

  osKernelStackInit(0);
  TCB_STACK[0][STACKSIZE - 2] = (uint32_t)thread0;

  osKernelStackInit(1);
  TCB_STACK[1][STACKSIZE - 2] = (uint32_t)thread1;

  osKernelStackInit(2);
  TCB_STACK[2][STACKSIZE - 2] = (uint32_t)thread2;

  // Initialize the currentPt
  currentPt = &tcbs[0];
  __enable_irq();
  return 1;
}

void osKernelLaunch(uint32_t quanta) {
  // Disable the SysTick
  SysTick->CTRL = 0;

  // Reset the initial value
  SysTick->VAL = 0;

  // Set the lowest priority (largest possible value)
  NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

  // Set the counter
  const uint32_t MILLIS_PRESCALER = SystemCoreClock / 1000;
  SysTick->LOAD = quanta * MILLIS_PRESCALER - 1;

  // Enable the SysTick source
  // enable = 1, tickint = 1, CLKSOURCE=Processor Clock (SystemCoreClock)
  SysTick->CTRL = 0x07;
  osSchedulerLaunch();
}

static const uint8_t PENDSTSET = 26;
void osKernelYield(void) {
  // Clear SysTick VAL since it can contain arbritary values
  SysTick->VAL = 0;

  // Raise the SysTick Interrupt
  SCB->ICSR = (1 << PENDSTSET);
}

// Static functions
static void osKernelStackInit(int thread_number) {
  // STACKSIZE = 100
  // Last value is 99
  // 100 - 16 => 84 uint32_t value to be stored
  tcbs[thread_number].stackPt = &TCB_STACK[thread_number][STACKSIZE - 16];

  // xPSR value needs to be in the thumb state
  // xPSR, PC, LR, r12, r3, r2, r1, r0
  // r11, r10, r9, r8, r7, r6, r5, r4
  TCB_STACK[thread_number][STACKSIZE - 1] = 0x01000000;
}
