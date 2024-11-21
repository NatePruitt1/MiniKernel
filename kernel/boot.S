#include "include/sysreg.h"

.section ".text.boot"
.globl _start

_start:
  mrs x0, mpidr_el1 //Set x1 to the cpu status system register
  and x0, x0, #3    //Extract the first 2 bits of this status register
  
  cmp x0, #0
  bne halt
  
  b el1_entry

kernel_init:
    ldr	x0, =SCTLR_VALUE_MMU_DISABLED
    msr	sctlr_el1, x0

    ldr	x0, =HCR_VALUE
	  msr	hcr_el2, x0

	  ldr	x0, =SCR_VALUE
	  msr	scr_el3, x0

	  ldr	x0, =SPSR_VALUE
	  msr	spsr_el3, x0
   
    adr x0, el1_entry
    msr elr_el3, x0
    eret

el1_entry:
	ldr x5, =__bss_start  //Set the bss start
  ldr w6, =__bss_size   //Set the bss size.
  1:                    //Loop from bss_size to 0
    cbz w6, 2f          //break if bss_size = 0
    str xzr, [x5], #8   //store 0 in [bss_start], and then increments bss_start reg.
    sub w6, w6, #1      //subtract 1 from bss_size
    cbnz w6, 1b         //loop if bss_size > 0
  2:  
  
  mov sp, #0x400000   //Set the stack start
	
  bl uart_init

  bl kernel_main

halt:                   //Protect from crash by busy-looping after main
  mov x1, #0            //prevents compiler removing
halt_inner:             //infinite loop
  wfe                   //wait for event
  b halt_inner          //infinite loop

// --------------------  Utilities  --------------------

.globl get_el
get_el:
  mrs x0, CurrentEL
  lsr x0, x0, #2
  ret

.globl _enable_irq
_enable_irq:
  msr daifclr, #0x2
  ret

.globl _disable_irq
_disable_irq:
  msr daifset, #0x2
  ret

.globl enable_vector_el1
enable_vector_el1:
  adr x0, vector_table
  msr vbar_el1, x0

// -------------------- Interrupt Macros --------------------    

.macro vector_entry label
  .align 7
  b \label
.endm

.macro enter_handler
  sub	sp, sp, #256
	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
	stp	x28, x29, [sp, #16 * 14]
	str	x30, [sp, #16 * 15]
.endm

.macro exit_handler
ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15] 
	add	sp, sp, #256
  eret
.endm

// -------------------- Vector Table --------------------

vector_table:
  //ELT table. For when the EL1 sp is the same as the EL0 sp
  vector_entry error_handler //Synchronous ELt
  vector_entry error_handler //IRQ
  vector_entry error_handler //FIQ
  vector_entry error_handler //SError
  
  //ELH table. For when the EL1 sp is different then the EL0 sp
  vector_entry error_handler //Synchronous ELt
  vector_entry error_handler //IRQ
  vector_entry error_handler //FIQ
  vector_entry error_handler //SError
  
  //EL0_64. For when the exception happened in EL0 64 bit mode
  vector_entry error_handler //Synchronous ELt
  vector_entry handle_el1_irq //IRQ
  vector_entry error_handler //FIQ
  vector_entry error_handler //SError
  
  //EL0_32. For when the exception happend in EL0 32 bit mode
  vector_entry error_handler //Synchronous ELt
  vector_entry error_handler //IRQ
  vector_entry error_handler //FIQ
  vector_entry error_handler //SError

// -------------------- Interrupt Handlers --------------------

handle_el1_irq:
  enter_handler
  bl handle_irq
  exit_handler

error_handler:
  enter_handler
  bl handle_error_interrupt
