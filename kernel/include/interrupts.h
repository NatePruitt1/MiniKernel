#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "mmio.h"

#define INTERRUPT_BASE (MMIO_BASE + 0xB000)
#define IRQ_BASIC_PENDING (INTERRUPT_BASE + 0x200)
#define IRQ_PENDING_1 (INTERRUPT_BASE + 0x204)
#define IRQ_PENDING_2 (INTERRUPT_BASE + 0x208)
#define FIQ_CONTROL (INTERRUPT_BASE + 0x20C)
#define ENABLE_IRQ_1 (INTERRUPT_BASE + 0x210)
#define ENABLE_IRQ_2 (INTERRUPT_BASE + 0x214)
#define DISABLE_IRQ_1 (INTERRUPT_BASE + 0x21C)
#define DISABLE_IRQ_2 (INTERRUPT_BASE + 0x220)

#define ARM_PERI_BASE 0x40000000
#define CORE0_TIMER_IRQCNTL (ARM_PERI_BASE + 0x40)

#if !defined(__ASSEMBLER__) && !defined(__ASSEMBLY__)
void handle_irq();
void handle_error_interrupt();
extern void _enable_irq();
extern void _disable_irq();
extern void enable_vector_el1();
#endif

#endif
