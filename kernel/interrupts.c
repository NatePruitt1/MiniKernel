#include "include/interrupts.h"
#include "include/mmio.h"
#include "include/timer.h"
#include "include/kdebug.h"

void enable_interrupt_controller() {
  mmio_write(ENABLE_IRQ_1, SYSTEM_TIMER_1);
}

void handle_irq() {
  unsigned int irq = mmio_read(IRQ_PENDING_1);
  if(irq & SYSTEM_TIMER_1) {
    handle_timer_irq();
  } else {
    kdebug("UNKNOWN INTERRUPT!");
  }
}
