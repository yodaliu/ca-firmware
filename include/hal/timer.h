#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "address.h"

#define SYS_TIMER_CS_M0     (1 << 0)
#define SYS_TIMER_CS_M1     (1 << 1)
#define SYS_TIMER_CS_M2     (1 << 2)
#define SYS_TIMER_CS_M3     (1 << 3)

#define SYS_TIMER_CS        (SYS_TIMER_BASE + 0x00)
#define SYS_TIMER_CLO       (SYS_TIMER_BASE + 0x04)
#define SYS_TIMER_CHI       (SYS_TIMER_BASE + 0x08)
#define SYS_TIMER_C0        (SYS_TIMER_BASE + 0x0C)
#define SYS_TIMER_C1        (SYS_TIMER_BASE + 0x10)
#define SYS_TIMER_C2        (SYS_TIMER_BASE + 0x14)
#define SYS_TIMER_C3        (SYS_TIMER_BASE + 0x18)

enum sys_timer_id {
    SYS_TIMER_0 = 0,
    SYS_TIMER_1 = 1,
    SYS_TIMER_2,
    SYS_TIMER_3
};

#define ARM_TIMER_LOAD      (ARMC_BASE + 0x400)
#define ARM_TIMER_VALUE     (ARMC_BASE + 0x404)
#define ARM_TIMER_CONTROL   (ARMC_BASE + 0x408)
#define ARM_TIMER_IRQCNTL   (ARMC_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ    (ARMC_BASE + 0x410)
#define ARM_TIMER_MSKIRQ    (ARMC_BASE + 0x414)
#define ARM_TIMER_RELOAD    (ARMC_BASE + 0x418)
#define ARM_TIMER_PREDIV    (ARMC_BASE + 0x41C)
#define ARM_TIMER_FREECNT   (ARMC_BASE + 0x420)

void enable_sys_timer_ms(
    enum sys_timer_id timer,
    uint32_t period
);

void disable_sys_timer(
    enum sys_timer_id timer
);

void enable_sys_timer_irq(
    enum sys_timer_id timer
);

void disable_sys_timer_irq(
    enum sys_timer_id timer
);

#endif //#ifndef _TIMER_H_
