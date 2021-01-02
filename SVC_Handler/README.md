- [SVC Handler](#svc-handler)
  - [ARM references](#arm-references)
  - [Some important links](#some-important-links)
- [Steps](#steps)

# SVC Handler

## ARM references

- [Usage of inline __ASM](https://developer.arm.com/documentation/100748/0615/Using-Assembly-and-Intrinsics-in-C-or-C---Code/Writing-inline-assembly-code)
- [Attribute list](https://www.keil.com/support/man/docs/armclang_ref/armclang_ref_jhg1476893564298.htm)
- [Writing SVC Exceptions](https://www.keil.com/support/docs/4063.htm)
- **The Definitive Guide to ARM® Cortex®-M3 and Cortex®-M4 Processors**
 by **Joseph Yiu**

## Some important links

- [ARM and Thumb Assembly instructions](https://www.keil.com/support/man/docs/armasm/armasm_dom1361289850039.htm)
- [Core Register](https://developer.arm.com/documentation/dui0552/a/the-cortex-m3-processor/programmers-model/core-registers?lang=en#:~:text=CONTROL%20register,-The%20CONTROL%20register&text=Defines%20the%20currently%20active%20stack,bit%20automatically%20on%20exception%20return.&text=1%20%3D%20PSP%20is%20the%20current%20stack%20pointer.)
- [Writing SVC Macro and SVC Handler function](https://stackoverflow.com/questions/60045830/stack-frame-not-correct-with-gcc-and-stm32)

# Steps

- The `svc` assembly instruction is used to create an interrupt between the user thread and a priviledged thread.
  - We can add different `svc` services using the `svc` instruction.
  - The `svc` instruction takes in an immediate value 8 bits in size.
  - Each `svc number` can be configured for a different service.
  - Calling the `svc` assembly instruction raises an interrupt `SVC_Handler`
- The `SVC_Handler` is a pure assembly function
  - **IMPORTANT** Mark this function with `__attribute((naked))`
  - We check the `lr` register to see if the `MSP` or `PSP` is used
  - We load this to `r0` and start the `SVC_Handler_Main` function
  - The `r0` is passed as an argument to `SVC_Handler_Main`
- Inside `SVC_Handler_Main` we can query the stack of the calling function
  - `svc_args` is the `MSP` or `PSP` of the calling function
  - Inside this function we can perform our **priviledged** tasks using the svc number and running a specific svc service according to that number
- We can return the value by writing to the various registers i.e `r0`, `r1`, `r2`, `r3`, `r12`
  - NOTE, More registers can also be pushed onto the stack if required
