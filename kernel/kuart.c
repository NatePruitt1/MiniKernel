#include "include/mmio.h"

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
