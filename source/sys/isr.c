#include <stdint.h>
#include <hal/aarch64.h>
#include <sys/io.h>

void virtual_timer_isr()
{

    uint32_t cntfrq, ticks;
    uint64_t current_cnt;

    disable_cntv();
    cntfrq = raw_read_cntfrq_el0();

    ticks = 5 * cntfrq;
    // Get value of the current timer
    current_cnt = raw_read_cntvct_el0();
    raw_write_cntv_cval_el0(current_cnt + ticks);

    enable_cntv();

}