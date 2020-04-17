#include <stdint.h>
#include <hal/timer.h>

void set_arm_timer_irq_route(void)
{
    uint32_t mpidr_el1, offset;

    mpidr_el1 = raw_read_mpidr_el1();
    offset = (mpidr_el1 & 0x3) << 2;

    put32((ARM_LOCAL_TIMER_CNTRL0 + offset), 0);
}