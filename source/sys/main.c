#include <hal/auxi.h>
#include <hal/timer.h>
#include <hal/gic.h>
#include <hal/aarch64.h>
#include <sys/utils.h>

#define TIMER_WAIT      1   /* Assert Timer IRQ after n secs */

static uint32_t cntfrq;     /* System frequency */

void main(void)
{
    uint32_t val;
    uint64_t ticks, current_cnt;

    uart_init();
    init_gic();

    printf("main\n");

    val = get_current_el();
    printf("CurrentEL = %x\n", val);

    val = raw_read_daif();
    printf("DAIF = %x\n", val);

    // Disable the timer
    disable_cntv();
    val = raw_read_cntv_ctl();
    printf("Disable the timer, CNTV_CTL_EL0 = %x\n", val);

    cntfrq = raw_read_cntfrq_el0();
    printf("System Frequency: CNTFRQ_EL0 = %x\n", cntfrq);

    // Next timer IRQ is after n sec(s).
    ticks = TIMER_WAIT * cntfrq;
    // Get value of the current timer
    current_cnt = raw_read_cntvct_el0();
    printf("Current counter: CNTVCT_EL0 = %x\n", current_cnt);

    // Set the interrupt in Current Time + TimerTick
    raw_write_cntv_cval_el0(current_cnt + ticks);
    val = raw_read_cntv_cval_el0();
    printf("Assert Timer IRQ after 1 sec: CNTV_CVAL_EL0 = %x\n", val);

    // Enable the timer
    enable_cntv();
    val = raw_read_cntv_ctl();
    printf("Enable the timer, CNTV_CTL_EL0 = %x\n", val);

    // Enable IRQ
    enable_irq();
    val = raw_read_daif();
    printf("Enable IRQ, DAIF = %x\n", val);
}