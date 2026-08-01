#include "include/mmio.h"
#include "include/utils.h"

void uart_init() {
  // Configure GPIO14/15 for PL011 TX/RX (ALT0).
  uint32_t selector = mmio_read(GPIO_FSEL1);
  selector &= ~(7 << 12);
  selector |= 4 << 12;
  selector &= ~(7 << 15);
  selector |= 4 << 15;

  mmio_write(GPIO_FSEL1, selector);
  mmio_write(GPPUD, 0);
  delay(150);
  mmio_write(GPPUDCLK0, (1<<14) | (1<<15));
  delay(150);
  mmio_write(GPPUDCLK0,0);

  // Initialize PL011 for 115200 8N1.
  mmio_write(UART0_CR, 0);
  mmio_write(UART0_ICR, 0x7FF);
  mmio_write(UART0_IBRD, 26);
  mmio_write(UART0_FBRD, 3);
  mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
  mmio_write(UART0_IMSC, 0);
  mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

//Kernel Uart Comms
void uart_wait_read() {
  while(mmio_read(UART0_FR) & (1 << 4));
}

void uart_wait_write() {
  while(mmio_read(UART0_FR) & (1 << 5));
}

char uart_read() {
  uart_wait_read();
  return mmio_read(UART0_DR);
}

void uart_write(char c) {
  uart_wait_write();
  mmio_write(UART0_DR, c);
}
