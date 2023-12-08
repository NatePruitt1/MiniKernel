#include "kdebug.h"
#include "kuart.h"

void kdebug(char *string) {
  int i;

  i = 0;
  while(string[i] != '\0') {
    uart_write(string[i]);
    ++i;
  }
}
