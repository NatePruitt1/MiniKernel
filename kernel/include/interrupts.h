enum {
  INTERRUPT_BASE = 0x7E00B000,
  IRQ_BASIC_PENDING = INTERRUPT_BASE + 0x200,
  IRQ_PENDING_1 = INTERRUPT_BASE + 0x204,
  IRQ_PENDING_2 = INTERRUPT_BASE + 0x208,
  FIQ_CONTROL = 0x20C,
  ENABLE_IRQ_1 = 0x210,
  ENABLE_IRQ_2 = 0x214,
  DISABLE_IRQ_1 = 0x21C,
  DISABLE_IRQ_2 = 0x220,

  SYSTEM_TIMER_1 = 0x1 << 1,
  SYSTEM_TIMER_3 = 0x1 << 3,
  USB_CONTROLLER = 0x1 << 9,
  AUX_INT = 0x1 << 29,

};

//Enables the interrupts needed from the interrupt controller.
void enable_timer_interrupts();

void enable_interrupt_controller(); 
void handle_irq();
void handle_error_interrupt();
void _enable_irq();
void _disable_irq();
void enable_vector_el1();
