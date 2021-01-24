  .text 32
  .align 4
  .syntax unified

@ By default we run an assembly function in an __attribute__((naked))
@ The values on the stack are not pushed or pop'ed
@ The equivalent of this function is written in inline assembly in `irq.c`
@ IT documentation: https://www.keil.com/support/man/docs/armasm/armasm_dom1361289872225.htm
  .global SVC_Handler
  .thumb_func
SVC_Handler:
  .global SVC_Handler_Main
  TST lr, #4     @ Does a bitwise AND i.e LR & (1 << 2) and updates xPSR register
  ITE EQ         @ Check Zero flag == 1 is EQ (runs first statement if EQ)
  MRSEQ r0, MSP  @ This is run if Zero Flag is set in xPSR register
  MRSNE r0, PSP  @ This is run in the else condition, opposite of EQ is NE
  B SVC_Handler_Main
