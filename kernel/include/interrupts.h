#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "mmio.h"
enum {
  INTERRUPT_BASE = MMIO_BASE + 0xB000,
  IRQ_BASIC_PENDING = INTERRUPT_BASE + 0x200,
  IRQ_PENDING_1 = INTERRUPT_BASE + 0x204,
  IRQ_PENDING_2 = INTERRUPT_BASE + 0x208,
  FIQ_CONTROL = INTERRUPT_BASE + 0x20C,
  ENABLE_IRQ_1 = INTERRUPT_BASE + 0x210,
  ENABLE_IRQ_2 = INTERRUPT_BASE + 0x214,
  DISABLE_IRQ_1 = INTERRUPT_BASE + 0x21C,
  DISABLE_IRQ_2 = INTERRUPT_BASE + 0x220,
};

void handle_irq();
void handle_error_interrupt();
extern void _enable_irq();
extern void _disable_irq();
extern void enable_vector_el1();

#endif
