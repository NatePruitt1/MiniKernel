#include <stddef.h>
#include <stdint.h>
#include "include/kdebug.h"
#include "include/interrupts.h"
#include "include/kuart.h"
#include "include/utils.h"

void handle_irq() {
  kdebug("Woah interrupt given.\n");
}

void handle_error_interrupt() {
  kdebug("Error interrupt.\n");
}

void kernel_main() {
  uart_init();
  enable_vector_el1();
  _enable_irq();
  kdebug("Hello, world from MiniKernel!\n");

  uint32_t el = get_el();

  kdebug("El: ");
  kdebug_number(el);
  kdebug("\n\r");

  char read[2] = {0};
  while(1) {
    read[0] = uart_read();
    kdebug(read);
  }
}
