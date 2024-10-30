#include "include/timer.h"
#include "include/mmio.h"
#include "include/kdebug.h"

const unsigned int interval = 20000;
unsigned int curTime = 0;

void timer_init() {
  curTime = mmio_read(TIMER_CLO);
  curTime += interval;
  mmio_write(TIMER_C1, curTime);
  kdebug("COMPARE TIME SET\n");
}

void handle_timer_irq() {
  //read and increment time.
  curTime += interval;

  //Write new time, and acknowledge timer 1.
  mmio_write(TIMER_C1, curTime);
  mmio_write(TIMER_CS, TIMER_CS_M1);

  kdebug("TIMER INTERRUPTED!");
}
