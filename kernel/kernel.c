#include <stddef.h>
#include <stdint.h>
#include "include/kdebug.h"
#include "include/interrupts.h"

void handle_irq() {
  kdebug("Woah interrupt given.\n");
}

void handle_error_interrupt() {
  kdebug("Error interrupt.\n");
}

void kernel_main() {
  
  while(1) {
  }
}
