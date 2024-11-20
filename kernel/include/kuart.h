#ifndef _UART_H
#define _UART_H

void uart_init();
void uart_wait_write();
void uart_wait_read();
void uart_write(char c);
char uart_read();

#endif
