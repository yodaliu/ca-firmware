#include <stdint.h>
#include <hal/timer.h>
#include <hal/armc.h>
#include <sys/io.h>

void enable_sys_timer_ms(enum sys_timer_id timer, uint32_t period)
{
    uint64_t val;

    val = get32(SYS_TIMER_CHI);
    val = val << 32;
    val |= get32(SYS_TIMER_CLO);

    val += period << 10;
    put32(SYS_TIMER_C0 + (timer << 2), val);

    val = get32(SYS_TIMER_CS) | (1 << timer);
    put32(SYS_TIMER_CS, val & 0xFFFFFFFF);
}

void disable_sys_timer(enum sys_timer_id timer)
{
    uint32_t val;

    val = get32(SYS_TIMER_CS) & ~(1 << timer);
    put32(SYS_TIMER_CS, val);
}

void enable_sys_timer_irq(enum sys_timer_id timer)
{
    uint32_t val;

    val = get32(ARMC_IRQ0_SET_EN_0) | (1 << timer);
    put32(ARMC_IRQ0_SET_EN_0, val);
}

void disable_sys_timer_irq(enum sys_timer_id timer)
{
    uint32_t val;

    val = get32(ARMC_IRQ0_SET_EN_0) & ~(1 << timer);
    put32(ARMC_IRQ0_SET_EN_0, val);
}