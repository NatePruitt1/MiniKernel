#ifndef TIMER_H
#define TIMER_H
#include "mmio.h"

enum {
  SYSTEM_TIMER_BASE = MMIO_BASE + 0x3000,
  TIMER_CS = SYSTEM_TIMER_BASE,
  TIMER_CS_M1 = 0x1 << 1,
  TIMER_CLO = SYSTEM_TIMER_BASE + 0x4,
  TIMER_C1 = SYSTEM_TIMER_BASE + 0x10
};

void timer_init();
void handle_timer_irq();
#endif
