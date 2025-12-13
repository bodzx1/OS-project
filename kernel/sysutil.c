#include "types.h"
#include "syscall.h"
#include "memlayout.h"


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

// uint64
// sys_getppid(void)
// {
//   // You'll need to implement this differently if proc.h causes issues
//   // Return a dummy value for testing
//   return 2;  // Assuming init process is always PID 2
// }

// ULTRA SIMPLE RAND - always returns increasing numbers
static uint64 simple_counter = 1000;

uint64
sys_sysrand(void)
{
  simple_counter = simple_counter * 1103515245 + 12345;
  return simple_counter & 0x7fffffff;
}
uint64
sys_shutdown(void)
{


  // Write 0x5555 to the SiFive Test device to trigger poweroff
    *(volatile uint32 *)R_TEST = 0x5555;

    // Halt the CPU (just in case qemu doesn't exit immediately)
    for(;;) {
        asm volatile("wfi");
    }
    //mapped RTEST to physical address 0x10000 in kernel virtual address space which triggers shutdown
    //before defining rtest kernel was trying to access 0x10000 which isnt mapped so it throwed a kernel trap


    return 0; // Never reached
}
