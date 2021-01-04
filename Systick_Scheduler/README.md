- [Preemptive SysTick Scheduler](#preemptive-systick-scheduler)
  - [Pre-Requisites](#pre-requisites)
  - [Steps](#steps)
    - [Adding Threads](#adding-threads)
    - [Launching Threads](#launching-threads)
    - [SysTick Handler](#systick-handler)
- [Cooperative SysTick Scheduler](#cooperative-systick-scheduler)
  - [Pre-requisites](#pre-requisites-1)
  - [Steps](#steps-1)
    - [Adding the `yield` function](#adding-the-yield-function)

# Preemptive SysTick Scheduler

- **Non Cooperative**
  - Does not contain a `yield` function
- Round Robin Scheduling using Circular linked list
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

## Steps

### Adding Threads

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

### Launching Threads

- Make sure your SysTick is configured appropriately (with an appropriate quanta size)
- Load the `SP` to `currentPt->stackPt`
- POP all values from `R4-R11`, `R0-R3`, `R12`
- POP `LR`

### SysTick Handler

- PUSH `R4-R11` on the stack
  - Including the above registers
- Store old `SP` to `currentPt`
- Move to the next linked list
  - `current = current->nextPt`
  - Load new `SP` to `currentPt->stackPt`

# Cooperative SysTick Scheduler

- **Cooperative**
  - Contains a `yield` function

## Pre-requisites

- Builds upon the **preemptive scheduler**
- The only difference is that tasks can yield back to the scheduler once their tasks are done

## Steps

### Adding the `yield` function

- According to the preemptive scheduler we assign time slices to each of the different threads(tasks)
  - Once the time for a particular thread is done the scheduler gives the next time slice to a different thread (Round Robin)
  - Each thread is forced to use the entirity of its time (cannot give control back to the scheduler if it chooses to)
- The `yield` function raises an SysTick interrupt so that re-scheduling can take place i.e the next task in the circular linked list gets time.

```c
// Raise the SysTick interrupt for rescheduling
SCB->ICSR = (1 << PENDSTSET);
```
