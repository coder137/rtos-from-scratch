- [No Semaphore](#no-semaphore)
- [Spinlock Semaphore](#spinlock-semaphore)
- [Cooperative Semaphore](#cooperative-semaphore)

# No Semaphore

- Whenever a common resource is being shared i.e UART, SPI, I2C, LCD, CAN interfaces etc simultaneous access can cause a lot of problems.

![No Semphore for UART](images/example1_no_semaphore.PNG)

- In the above example we are writing data to the UART from thread 1 and thread 2
- As you can see in the image above when writing to the UART Task1/Task2 might be pre-empted before the entire data can be written to the UART
- The above problem of shared resources can be solved using Semaphores
- Semaphores are essentially signals that can signal certain parts of the code when something is done/needs to be done.

# Spinlock Semaphore

> TODO,

# Cooperative Semaphore

> TODO,
