#include <stddef.h>
#include <stdint.h>
#include "mmio.h"
#include "kdebug.h"
#include "kuart.h"

static void uart_init() {
  //setup gpio BEFORE uart1 enable
  //we are on 14 and 15
  //disable push/pull on 14 and 15
  mmio_write(GPPUD, (uint32_t)0);
  int i = 0;
  while(i < 150) i++;

  uint32_t c = mmio_read(GPPUDCLK0);
  c |= (1 << 14) | (1 << 15);
  mmio_write(GPPUDCLK0, c);
  i = 0;
  while(i < 150) i++;

  mmio_write(GPPUD, 0);
  c = mmio_read(GPPUDCLK0);
  c &= ~((1<<14) | (1<<15));
  
  //pins 14 and 15 are push pull disabled
  //enable their alt5 functions (TX1 and RX1)
  uint32_t alt5 = 0x2;
  uint32_t currsel = mmio_read(GPIO_FSEL1);
  currsel &= ~(0x3F << 12);
  currsel |= (alt5 << 12) | (alt5 << 15);
  mmio_write(GPIO_FSEL1, currsel);

  //gpio pins are setup
  //setup uart1
  mmio_write(AUX_ENABLES, (uint32_t)0x1);
  mmio_write(AUX_INTERRUPT_ENABLE, 0x0); //disable interrupts
  mmio_write(AUX_LINE_CNTL, 0x1);
  mmio_write(AUX_BAUD, (uint32_t)270);

}

void kernel_main(uint64_t dtb_ptr32, uint64_t cpu) {
	uart_init();

  if(cpu == 0) {
    char* christmas[9] = {
      "          *\n",
      "         *~*\n",
      "        *~*o*\n",
      "       **o*~**\n",
      "      **~****~*\n",
      "     **~*~***~**\n",
      "    *******o*****\n",
      "   ***o***********\n",
      "         | |\n"
    };

    for(int i = 0; i < 9; i++) {
      kdebug(christmas[i]);
    }

    kdebug("Merry Christmas!\n"); 
    kdebug("Author: Nate Pruitt\n");
    kdebug("Welcome to mini-kernel version 0.01\n");

    kdebug_number(10);
    kdebug("hello");
  }
}

