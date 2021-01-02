#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gpio/gpio.h"
#include "uart/uart.h"

// NOTE, code cannot be a variable it has to be an immediate value (constant
// value)
#define SVC(code) __ASM volatile("svc %0" : : "I"(code) : "memory")

// Static functions

// SVC Services
static uint32_t svc_service_add(uint32_t a, uint32_t b);
// TODO, Define more svc services here

// UART
static void main__uart_init(void);

// State Variables
static UART_s uart_config;

// Stack contains:
// (When there is NO floating point)
// Page 40 of `Cortex M4 Generic User guide`
// r0, r1, r2, r3, r12, LR, PC and xPSR (from svc_args[0] - svc_args[7])
// First argument (r0) is svc_args[0]
// PC - 2
void SVC_Handler_Main(unsigned int *svc_args) {
  // char *r0_address = (char *)svc_args[0];
  // char *lr_address = (char *)svc_args[5];
  // char *pc_address = (char *)svc_args[6];

  uint32_t svc_number = ((char *)svc_args[6])[-2];
  switch (svc_number) {
  // Add operation
  case 3:
    svc_args[2] = svc_args[0] + svc_args[1];
    break;
  default:
    break;
  }
}

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

int main(void) {
  main__uart_init();
  uart__write_string(&uart_config, "Hello World\r\n");
  char buffer[20] = {0};

  uint32_t value, new_value;
  value = svc_service_add(3, 4);
  __itoa(value, buffer, 10);
  uart__write_string(&uart_config, buffer);
  memset(buffer, 0, sizeof(buffer));

  new_value = svc_service_add(2, 3);
  __itoa(new_value, buffer, 10);
  uart__write_string(&uart_config, buffer);
  memset(buffer, 0, sizeof(buffer));

  (void)value;
  (void)new_value;

  while (1) {
  }

  return 0;
}

// STATIC FUNCTION
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

uint32_t svc_service_add(uint32_t a, uint32_t b) {
  SVC(3);
  // Named Register Variables
  register uint32_t r2_data __ASM("r2");
  return r2_data;
}
