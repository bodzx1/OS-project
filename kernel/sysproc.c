#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#ifndef BOOT_EPOCH
#define BOOT_EPOCH 0
#endif
uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}



uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint64
mtime_read(void)
{
  // Read the 64-bit MTIME register (requires the address to be mapped)
  // Use 'volatile' to ensure the compiler doesn't optimize the memory access away
  return *(volatile uint64*)MTIME;
}
extern uint64 boot_epoch;
#define SECS_PER_MIN (60)
#define SECS_PER_HOUR (3600)
#define SECS_PER_DAY (SECS_PER_HOUR * 24)
#define DAYS_PER_YEAR (365)
#define LEAP_YEAR_FREQ (4)
#define DAYS_PER_LEAP_YEAR (366)
static int days_in_month[] = {
  0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
uint64
sys_datetime(void)
{
  // The structure to hold the calculated time
  struct datetime r;
  uint64 user_addr;
  //uint64 time_since_boot_ticks;
  uint64 cycles=mtime_read();
  uint64 total_seconds;

  // Local variables for date conversion
  long days;
  long seconds;
  int year;
  int month;
  // 1. Get the destination address from the user stack
  // Fix for error 1: argaddr does not return a value.
  argaddr(0, &user_addr);

  // 2. Safely get system uptime (in seconds)
  //acquire(&tickslock);
  //time_since_boot_ticks = ticks;
  //release(&tickslock);

  // Convert ticks (assuming 100 Hz in xv6) to seconds
  //uint64 seconds_since_boot = time_since_boot_ticks / 100;
  uint64 seconds_since_boot=cycles/10000000; //mtime is more precise than ticks so i used it
  // total_seconds = (uint64)BOOT_EPOCH + seconds_since_boot;

  // BUILD_TIME is seconds since Jan 1, 1970 (defined in Makefile)
  total_seconds = (uint64)BOOT_EPOCH + seconds_since_boot+7200;

  // 3. --- TIME CONVERSION LOGIC (Fix for error 2) ---

  // Calculate seconds remaining in the day
  r.second = (uint)(total_seconds % 60);
  seconds = total_seconds / SECS_PER_MIN;

  // Calculate minutes and hours remaining
  r.minute = (uint)(seconds % 60);
  seconds /= 60;
  r.hour = (uint)(seconds % 24);

  // Total days since epoch (Jan 1, 1970 is day 0)
  days = seconds / 24;

  // Calculate Year, Month, Day
  year = 1970;
  while(days >= 0) {
    int days_in_cur_year = (year % LEAP_YEAR_FREQ == 0 && year % 100 != 0) || (year % 400 == 0) ? DAYS_PER_LEAP_YEAR : DAYS_PER_YEAR;

    if (days < days_in_cur_year) {
      break; // Found the current year
    }
    days -= days_in_cur_year;
    year++;
  }
  r.year = year;

  // Calculate Month and Day
  month = 1;
  while(month <= 12) {
    int days_in_cur_month = days_in_month[month];
    // Adjust February for leap year
    if (month == 2 && ((year % LEAP_YEAR_FREQ == 0 && year % 100 != 0) || (year % 400 == 0))) {
      days_in_cur_month = 29;
    }

    if (days < days_in_cur_month) {
      break; // Found the current month
    }
    days -= days_in_cur_month;
    month++;
  }
  r.month = month;

  // Remaining days (plus 1 since days started at 0)
  r.day = (uint)days + 1;

  // 4. Copy the structure back to user space
  if(copyout(myproc()->pagetable, user_addr, (char*)&r, sizeof(r)) < 0)
    return -1;

  return 0;
}
uint64
sys_getptable(void)
{
  int nproc;
  uint64 addr;

  argint(0, &nproc);
  argaddr(1, &addr);

  return getptable(nproc, (char *)addr);
}
