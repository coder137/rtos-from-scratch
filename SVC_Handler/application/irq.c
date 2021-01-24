#include "stm32l475xx.h"

// * This attribute is VERY IMPORTANT
// Compile with O0 to see the difference with and without
// the __attribute__((naked)) option
__attribute__((naked)) void SVC_Handler(void) {
  __ASM volatile(".global SVC_Handler_Main\n"
                 "TST lr, #4\n"
                 "ITE EQ\n"
                 "MRSEQ r0, MSP\n"
                 "MRSNE r0, PSP\n"
                 "B SVC_Handler_Main\n" ::
                     : "memory");
}
