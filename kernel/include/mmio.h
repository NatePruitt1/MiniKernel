#ifndef MMIO_H
#define MMIO_H

#if !defined(__ASSEMBLER__) && !defined(__ASSEMBLY__)
#include <stdint.h>
#endif

#define MMIO_BASE 0x3F000000
// The offsets for reach register.
#define GPIO_BASE 0x200000

// Controls actuation of pull up/down to ALL GPIO pins.
#define GPPUD (MMIO_BASE + GPIO_BASE + 0x94)

// Controls actuation of pull up/down for specific GPIO pin.
#define GPPUDCLK0 (MMIO_BASE + GPIO_BASE + 0x98)

#define GPIO_FSEL1 (MMIO_BASE + GPIO_BASE + 0x4)

// The base address for UART.
#define AUX_BASE (MMIO_BASE + GPIO_BASE + 0x15000)
#define AUX_INTERRUPT_STATUS (AUX_BASE)
#define AUX_ENABLES (AUX_BASE + 0x4)
#define AUX_IO (AUX_BASE + 0x40)
#define AUX_INTERRUPT_ENABLE (AUX_BASE + 0x44)
#define AUX_INTERRUPT_IDENTIFY (AUX_BASE + 0x48)
#define AUX_LINE_CNTL (AUX_BASE + 0x4C)
#define AUX_MODEM_CNTL (AUX_BASE + 0x50)
#define AUX_LINE_STATUS (AUX_BASE + 0x54)
#define AUX_SCRATCH (AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)
#define AUX_EXTRA_STAT (AUX_BASE + 0x64)
#define AUX_BAUD (AUX_BASE + 0x68)

// PL011 UART0 (supported by QEMU raspi3 model).
#define UART0_BASE (MMIO_BASE + 0x201000)
#define UART0_DR (UART0_BASE + 0x00)
#define UART0_FR (UART0_BASE + 0x18)
#define UART0_IBRD (UART0_BASE + 0x24)
#define UART0_FBRD (UART0_BASE + 0x28)
#define UART0_LCRH (UART0_BASE + 0x2C)
#define UART0_CR (UART0_BASE + 0x30)
#define UART0_IMSC (UART0_BASE + 0x38)
#define UART0_ICR (UART0_BASE + 0x44)

#if !defined(__ASSEMBLER__) && !defined(__ASSEMBLY__)
extern void mmio_write(uint32_t reg, uint32_t data);
extern uint32_t mmio_read(uint32_t reg);
#endif

#endif
