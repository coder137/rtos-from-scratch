#include "osKernel.h"

// * Add these variables to the debug watch window
static uint32_t i, j, k;

void t1(void) {
  while (1) {
    i++;
    osKernelYield();
  }
}

void t2(void) {
  while (1) {
    j++;
  }
}

void t3(void) {
  while (1) {
    k++;
  }
}

int main(void) {
  osKernelAddThreads(t1, t2, t3);
  osKernelLaunch(10);
  while (1) {
  }

  return 0;
}
