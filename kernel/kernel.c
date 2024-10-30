#include <stddef.h>
#include <stdint.h>
#include "include/mmio.h"
#include "include/kdebug.h"
#include "include/kuart.h"
#include "include/interrupts.h"

void handle_error_interrupt() {
  kdebug("Error interrupt.\n");
}

static void uart_init() {
  uint32_t selector = mmio_read(GPIO_FSEL1);
  selector &= ~(7 << 12);
  selector |= 2 << 12;
  selector &= ~(7 << 15);
  selector |= 2 << 15;

  mmio_write(GPIO_FSEL1, selector);
  mmio_write(GPPUD, 0);
  for(volatile int i = 0; i < 150; i++){}
  mmio_write(GPPUDCLK0, (1<<14) | (1<<15));
  for(volatile int i = 0; i < 150; i++){}
  mmio_write(GPPUDCLK0,0);

  mmio_write(AUX_ENABLES, 1);
  mmio_write(AUX_MU_CNTL_REG, 0);
  mmio_write(AUX_INTERRUPT_ENABLE, 0);
  mmio_write(AUX_LINE_CNTL, 3);
  mmio_write(AUX_MODEM_CNTL, 0);
  mmio_write(AUX_BAUD, 270);
  
  mmio_write(AUX_MU_CNTL_REG, 3);
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

