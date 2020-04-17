#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include <hal/address.h>

#define SYS_TIMER_CS    (SYS_TIMER_BASE + 0x00)
#define SYS_TIMER_CLO   (SYS_TIMER_BASE + 0x04)
#define SYS_TIMER_CHI   (SYS_TIMER_BASE + 0x08)
#define SYS_TIMER_C0    (SYS_TIMER_BASE + 0x0C)
#define SYS_TIMER_C1    (SYS_TIMER_BASE + 0x10)
#define SYS_TIMER_C2    (SYS_TIMER_BASE + 0x14)
#define SYS_TIMER_C3    (SYS_TIMER_BASE + 0x18)

#define ARM_TIMER_LOAD      (ARMC_BASE + 0x400)
#define ARM_TIMER_VALUE     (ARMC_BASE + 0x404)
#define ARM_TIMER_CONTROL   (ARMC_BASE + 0x408)
#define ARM_TIMER_IRQCNTL   (ARMC_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ    (ARMC_BASE + 0x410)
#define ARM_TIMER_MSKIRQ    (ARMC_BASE + 0x414)
#define ARM_TIMER_RELOAD    (ARMC_BASE + 0x418)
#define ARM_TIMER_PREDIV    (ARMC_BASE + 0x41C)
#define ARM_TIMER_FREECNT   (ARMC_BASE + 0x420)

#define ARM_LOCAL_TIMER_CNTRL0  (ARM_LOCAL_BASE + 0x40)
#define ARM_LOCAL_TIMER_CNTRL1  (ARM_LOCAL_BASE + 0x44)
#define ARM_LOCAL_TIMER_CNTRL2  (ARM_LOCAL_BASE + 0x48)
#define ARM_LOCAL_TIMER_CNTRL3  (ARM_LOCAL_BASE + 0x4C)

void set_arm_timer_irq_route(
    void
);

#endif //#ifndef _TIMER_H_
