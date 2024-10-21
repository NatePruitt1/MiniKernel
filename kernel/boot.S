.section ".text.boot"
.globl _start

.org 0x80000

_start://at 0x80000 now for kernel start
  mrs x1, mpidr_el1 //Set x1 to the cpu status system register
  and x1, x1, #3    //Extract the first 2 bits of this status register


  //set stack 
  ldr x5, =_start   //Set the stack start
  mov sp, x5        //Move the stack pointer to stack start.

  //clear the bss section
  ldr x5, =__bss_start  //Set the bss start
  ldr w6, =__bss_size   //Set the bss size.
  1:                    //Loop from bss_size to 0
    cbz w6, 2f          //break if bss_size = 0
    str xzr, [x5], #8   //store 0 in [bss_start], and then increments bss_start reg.
    sub w6, w6, #1      //subtract 1 from bss_size
    cbnz w6, 1b         //loop if bss_size > 0

  2: bl kernel_main     //Call kernel main

halt:                   //Protect from crash by busy-looping after main
  mov x1, #0            //prevents compiler removing
halt_inner:             //infinite loop
  wfe                   //wait for event
  b halt_inner          //infinite loop

.balign 32
vector_table:
  bl empty_handler  //reset
  bl empty_handler  //undefined
  bl empty_handler  //svc
  bl empty_handler  //prefetch 
  bl empty_handler  //data
  nop
  bl empty_handler  //irq
  bl empty_handler  //fiq
