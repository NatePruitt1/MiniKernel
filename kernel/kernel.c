#include <stddef.h>
#include <stdint.h>
#include "include/mmio.h"
#include "include/kdebug.h"
#include "include/kuart.h"
#include "include/interrupts.h"

void handle_error_interrupt() {
  kdebug("Error interrupt.\n");
}

void kernel_main(uint64_t dtb_ptr32, uint64_t cpu) {
	if(cpu == 0) {
    uart_init();
    kdebug("Hello!!\n");
    while(1) {
      kdebug("H");
    }
  }
  
}

