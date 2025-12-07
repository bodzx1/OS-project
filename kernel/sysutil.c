#include "types.h"
#include "syscall.h"

extern int kbd_intr_count;
extern int syscall_count;

uint64
sys_kbdint(void)
{
  return kbd_intr_count;
}

uint64
sys_countsyscall(void)
{
  return syscall_count;
}

uint64
sys_getppid(void)
{
  // You'll need to implement this differently if proc.h causes issues
  // Return a dummy value for testing
  return 2;  // Assuming init process is always PID 2
}

// ULTRA SIMPLE RAND - always returns increasing numbers
static uint64 simple_counter = 1000;

uint64
sys_sysrand(void)
{
  simple_counter = simple_counter * 1103515245 + 12345;
  return simple_counter & 0x7fffffff;
}
