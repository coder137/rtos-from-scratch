#include "osKernel.h"
#include "osSemaphore.h"

#include "gpio/gpio.h"
#include "uart/uart.h"

// UART
static void main__uart_init(void);

// State Variables
static UART_s uart_config;

// * Add these variables to the debug watch window
static uint32_t i, j, k;
static uint32_t semaphore_t1, semaphore_t2;

void t1(void) {
  while (1) {
    osSemaphoreWait(&semaphore_t1);
    i++;
    uart__write_string(&uart_config, "Hello World from Thread 1\r\n");
    osSemaphoreSignal(&semaphore_t2);
  }
}

void t2(void) {
  while (1) {
    osSemaphoreWait(&semaphore_t2);
    j++;
    uart__write_string(&uart_config, "Hello World from Thread 2\r\n");
    osSemaphoreSignal(&semaphore_t1);
  }
}

void t3(void) {
  while (1) {
    k++;
  }
}

int main(void) {
  osSemaphoreInit(&semaphore_t1, 1);
  osSemaphoreInit(&semaphore_t2, 0);

  main__uart_init();
  uart__write_string(&uart_config, "Hello World\r\n");

  osKernelAddThreads(t1, t2, t3);
  osKernelLaunch(10);
  while (1) {
  }

  return 0;
}

static void main__uart_init(void) {
  // Activate USART1
  RCC->APB2ENR |= (1 << 14);
  // Activate GPIOB
  RCC->AHB2ENR |= (1 << 1);

  GPIO_s config = {};
  config.mode = GPIO_mode_ALTERNATE_FUNCTION;
  config.type = GPIO_type_PUSH_PULL;
  config.speed = GPIO_speed_VERY_HIGH_SPEED;
  config.pull = GPIO_pull_NO_PULLUP_OR_PULLDOWN;
  config.alternate = GPIO_alternate_7;
  gpio__init(&config, GPIOB, 6);
  gpio__init(&config, GPIOB, 7);

  uart_config.baud_rate = 115200U;
  uart_config.stop_bit = UART_stop_bit_1_0;
  uart_config.word_length = UART_word_length_8;
  uart_config.mode = UART_mode_RX_TX;
  uart__init(&uart_config, USART1);
}
