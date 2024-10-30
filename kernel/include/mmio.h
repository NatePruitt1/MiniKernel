#ifndef MMIO_H
#define MMIO_H
#include <stdint.h>

enum {
  MMIO_BASE = 0x3F000000,
  // The offsets for reach register.
  GPIO_BASE = 0x200000,

  // Controls actuation of pull up/down to ALL GPIO pins.
  GPPUD = (GPIO_BASE + 0x94),

  // Controls actuation of pull up/down for specific GPIO pin.
  GPPUDCLK0 = (GPIO_BASE + 0x98),

  GPIO_FSEL1 = GPIO_BASE + 0x4,

  // The base address for UART.
  AUX_BASE = 0x3F215000,
  AUX_INTERRUPT_STATUS = AUX_BASE,
  AUX_ENABLES = AUX_BASE + 0x4,
  AUX_IO = AUX_BASE + 0x40,
  AUX_INTERRUPT_ENABLE = AUX_BASE + 0x44,
  AUX_INTERRUPT_IDENTIFY = AUX_BASE + 0x48,
  AUX_LINE_CNTL = AUX_BASE + 0x4C,
  AUX_MODEM_CNTL = AUX_BASE + 0x50,
  AUX_LINE_STATUS = AUX_BASE + 0x54,
  AUX_SCRATCH = AUX_BASE + 0x5C,
  AUX_MU_CNTL_REG = AUX_BASE + 0x60,
  AUX_EXTRA_STAT = AUX_BASE + 0x64,
  AUX_BAUD = AUX_BASE + 0x68,
};

void mmio_write(uint32_t reg, uint32_t data);
uint32_t mmio_read(uint32_t reg);
#endif
