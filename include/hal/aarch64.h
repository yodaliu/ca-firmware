#ifndef _AARCH64_H_
#define _AARCH64_H_

#include "../sys/utils.h"

/* CurrentEL, Current Exception Level */
#define CURRENT_EL_MASK           0x3
#define CURRENT_EL_SHIFT          2

/* DAIF, Interrupt Mask Bits */
#define DAIF_DBG_BIT              BIT(3)  /* Debug mask bit */
#define DAIF_ABT_BIT              BIT(2)  /* Asynchronous abort mask bit */
#define DAIF_IRQ_BIT              BIT(1)  /* IRQ mask bit */
#define DAIF_FIQ_BIT              BIT(0)  /* FIQ mask bit */

/* Timer */
#define CNTV_CTL_ENABLE           BIT(0)    /* Enables the timer */
#define CNTV_CTL_IMASK            BIT(1)    /* Timer interrupt mask bit */
#define CNTV_CTL_ISTATUS          BIT(2)    /* The status of the timer interrupt. This bit is read-only */

/*
 * Interrupt flags
 */
#define AARCH64_DAIF_FIQ          (1)     /* FIQ */
#define AARCH64_DAIF_IRQ          (2)     /* IRQ */

/* Wait For Interrupt */
#define wfi()       asm volatile("wfi" : : : "memory")
#define wfe()       asm volatile("wfe" : : : "memory")

#ifndef __ASSEMBLY__
#include <stdint.h>
uint32_t raw_read_current_el(
    void
);

uint32_t get_current_el(
    void
);

uint32_t raw_read_daif(
    void
);

void raw_write_daif(
    uint32_t daif
);

void enable_debug_exceptions(
    void
);

void enable_serror_exceptions(
    void
);

void enable_irq(
    void
);

void enable_fiq(
    void
);

void disable_debug_exceptions(
    void
);

void disable_serror_exceptions(
    void
);

void disable_irq(
    void
);

void disable_fiq(
    void
);

uint32_t raw_read_spsr_el3(
    void
);

void raw_write_spsr_el3(
    uint32_t spsr_el3
);

uint32_t raw_read_isr_el1(
    void
);

uint64_t raw_read_rvbar_el3(
    void
);

void raw_write_rvbar_el3(
    uint64_t rvbar_el3
);

uint64_t raw_read_vbar_el3(
    void
);

void raw_write_vbar_el3(
    uint64_t vbar_el3
);


uint32_t raw_read_cntv_ctl(
    void
);

void disable_cntv(
    void
);

void enable_cntv(
    void
);

uint32_t raw_read_cntfrq_el0(
    void
);

void raw_write_cntfrq_el0(
    uint32_t cntfrq_el0
);

uint64_t raw_read_cntvct_el0(
    void
);

uint64_t raw_read_cntv_cval_el0(
    void
);

void raw_write_cntv_cval_el0(
    uint64_t cntv_cval_el0
);

uint32_t raw_read_mpidr_el1(
    void
);

#endif //#ifndef __ASSEMBLY__
#endif //#ifndef _AARCH64_H_