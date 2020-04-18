#include <hal/auxi.h>
#include <hal/timer.h>
#include <hal/arm_local.h>
#include <hal/aarch64.h>
#include <sys/utils.h>
#include <sys/io.h>

void main(void)
{
    uint32_t val, cntfrq, ticks, current_cnt;

    uart_init();

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
    ticks = 10 * cntfrq;
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

    put32(ARM_LOCAL_TIMER_CNTRL0, CNT_V_IRQ_FIQ);

    enable_irq();
    enable_fiq();

    val = raw_read_daif();
    printf("Enable IRQ, DAIF = %x\n", val);

    while (1) {


    }
}