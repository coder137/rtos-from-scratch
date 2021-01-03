  .global currentPt

  .text 32
  .align 4
  .syntax unified

  .global SysTick_Handler
  .thumb_func
SysTick_Handler:
  CPSID i
  PUSH {R4-R11}
  LDR R0,=currentPt     @ R0 points to currentPt
  LDR R1,[R0]           @ Load currentPt to R1
  STR SP,[R1]           @ Store SP to address at current->stackPt
  LDR R1, [R1, #4]      @ r1 = currentPt->next
  STR R1, [R0]          @ currentPt = r1
  LDR SP, [R1]          @ SP = currentPt->stackPt
  POP {R4-R11}
  CPSIE i
  BX LR


  .global osSchedulerLaunch
  .thumb_func
osSchedulerLaunch:
  LDR R0,=currentPt
  LDR R2,[R0]       @ R2 = currentPt
  LDR SP,[R2]       @ SP = currentPt->stackPt
  POP {R4-R11}
  POP {R0-R3}
  POP {R12}
  ADD SP,SP,#4
  POP {LR}
  ADD SP,SP,#4
  CPSIE i
  BX LR
