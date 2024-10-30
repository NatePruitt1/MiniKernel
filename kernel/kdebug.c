#include "include/kdebug.h"
#include "include/kuart.h"
#include <stdint.h>

void kdebug(char *string) {
  int i;

  i = 0;
  while(string[i] != '\0') {
    uart_write(string[i]);
    ++i;
  }
}

void kdebug_number(uint64_t num) {
  char str[20];
  char out[20];
  int i = 0;
 
  str[i] = '0' + num%10;
  num /= 10;
  ++i;
  while(num > 0){
    str[i] = '0' + num%10;
    num /= 10;
    ++i;
  }

  int len = i;
  for(int j = 0; j < len; j++){
    out[j] = str[i - 1];
    --i;
  }

  kdebug(out);
}
