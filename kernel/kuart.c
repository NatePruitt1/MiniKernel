#include "include/mmio.h"

void uart_init() {
  uint32_t selector = mmio_read(GPIO_FSEL1);
  selector &= ~(7 << 12);
  selector |= 2 << 12;
  selector &= ~(7 << 15);
  selector |= 2 << 15;

  mmio_write(GPIO_FSEL1, selector);
  mmio_write(GPPUD, 0);
  delay(150);
  mmio_write(GPPUDCLK0, (1<<14) | (1<<15));
  delay(150);
  mmio_write(GPPUDCLK0,0);

  mmio_write(AUX_ENABLES, 1);
  mmio_write(AUX_MU_CNTL_REG, 0);
  mmio_write(AUX_INTERRUPT_ENABLE, 0);
  mmio_write(AUX_LINE_CNTL, 3);
  mmio_write(AUX_MODEM_CNTL, 0);
  mmio_write(AUX_BAUD, 270);
  
  mmio_write(AUX_MU_CNTL_REG, 3);
}

//Kernel Uart Comms
void uart_wait_read() {
  while(!(mmio_read(AUX_LINE_STATUS) & 0x1));
}

void uart_wait_write() {
  while(!(mmio_read(AUX_LINE_STATUS) & (0x1 << 5)));
}

char uart_read() {
  uart_wait_read();
  return mmio_read(AUX_IO); 
}

void uart_write(char c) {
  uart_wait_write();
  mmio_write(AUX_IO, c);
}
