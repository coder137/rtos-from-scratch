# SysTick Scheduler

- Does not contain priorities
- Currently cannot dynamically add threads

## Pre-Requisites

- Linked List for stack and thread functions
```c
struct tcb {
  uint32_t *stackPt;
  struct tcb *nextPt;
};
typedef struct tcb tcbType;
```
- Scheduler Launch
- Systick Handler for loading threads and timekeeping

# Steps

## Adding Threads

- Each `tcb.nextPt` should point to the next `tcb`
  - The last `tcb` should point to the first `tcb` as a linked list
- The `tcb.stackPt` should point to the first free stack space that can be used
  - `[STACKSIZE - 16]`
  - In ascending to descending order (99-84)
  - xPSR
  - PC
  - LR
  - r12
  - r3
  - r2
  - r1
  - r0
  - r11
  - r10
  - r9
  - r8
  - r7
  - r6
  - r5
  - r4
- Make sure `xPSR` register is in thumb state i.e `[STACKSIZE - 1] = 0x01000000;`
- Make sure `PC` register points to the thread function

## Launching Threads

- Make sure your SysTick is configured appropriately (with an appropriate quanta size)
- Load the `SP` to `currentPt->stackPt`
- POP all values from `R4-R11`, `R0-R3`, `R12`
- POP `LR`

## SysTick Handler

- PUSH `R4-R11` on the stack
  - Including the above registers
- Store old `SP` to `currentPt->stackPt`
- Move to the next linked list
  - `current = current->nextPt`
  - Load new `SP` to `currentPt->stackPt`
