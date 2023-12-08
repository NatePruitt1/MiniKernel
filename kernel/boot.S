.section ".text.boot"
.globl _start

.org 0x80000

_start://at 0x80000 now for kernel start
  mrs x1, mpidr_el1
  and x1, x1, #3


  //set stack 
  ldr x5, =_start
  mov sp, x5

  //clear the bss section
  ldr x5, =__bss_start
  ldr w6, =__bss_size
  1:
    cbz w6, 2f
    str xzr, [x5], #8
    sub w6, w6, #1
    cbnz w6, 1b

  2: bl kernel_main

halt:
  mov x1, #0
halt_inner:
  wfe
  b halt_inner
