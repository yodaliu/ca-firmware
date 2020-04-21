#include <hal/uart.h>
#include <hal/aarch64.h>
#include <hal/gicv2.h>
#include <sys/utils.h>
#include <sys/io.h>

void main(void)
{
    uint32_t cntfrq, ticks;
    uint64_t current_cnt;

    uart_init();
    init_gicd();
    init_gicc();

    printf("main\n");

    // Disable the timer
    disable_cntv();
    cntfrq = raw_read_cntfrq_el0();

    // Next timer IRQ is after n sec(s).
    ticks = 5 * cntfrq;
    // Get value of the current timer
    current_cnt = raw_read_cntvct_el0();

    // Set the interrupt in Current Time + TimerTick
    raw_write_cntv_cval_el0(current_cnt + ticks);

    // Enable the timer
    enable_cntv();

    //put32(ARM_LOCAL_TIMER_CNTRL0, CNT_V_IRQ);
    enable_intrpt(GIC_ARM_IRQ_V_TIMER);

    enable_irq();
    enable_fiq();

    while (1) {


    }
}