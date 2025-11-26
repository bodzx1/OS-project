#include "types.h"
extern int kbd_interrupt_counter;
uint64 sys_kbdint(void)
{
  return kbd_interrupt_counter;

};
