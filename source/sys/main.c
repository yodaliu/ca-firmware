#include <hal/uart.h>
#include <hal/timer.h>
#include <hal/arm_local.h>
#include <hal/aarch64.h>
#include <sys/utils.h>
#include <sys/io.h>

#define MIN_SGI_ID      (0)
#define MIN_SEC_SGI_ID      (8)
#define MIN_PPI_ID      (16)
#define MIN_SPI_ID      (32)
#define MAX_SPI_ID      (1019)

#define TOTAL_SPI_INTR_NUM  (MAX_SPI_ID - MIN_SPI_ID + (1))
#define TOTAL_PCPU_INTR_NUM (MIN_SPI_ID - MIN_SGI_ID)

/* Highest possible interrupt priorities */
#define GIC_HIGHEST_SEC_PRIORITY    (0x00)
#define GIC_HIGHEST_NS_PRIORITY     (0x80)

/* GICD_TYPER shifts and masks */
#define TYPER_IT_LINES_NO_SHIFT (0)
#define TYPER_IT_LINES_NO_MASK  (0x1f)



#define GICD_BASE           0xff841000

#define GICD_CTLR           (GICD_BASE + 0x0)
#define GICD_TYPER          (GICD_BASE + 0x4)
#define GICD_IIDR           (GICD_BASE + 0x8)
#define GICD_IGROUPR        (GICD_BASE + 0x80)
#define GICD_ISENABLER      (GICD_BASE + 0x100)
#define GICD_ICENABLER      (GICD_BASE + 0x180)
#define GICD_ISPENDR        (GICD_BASE + 0x200)
#define GICD_ICPENDR        (GICD_BASE + 0x280)
#define GICD_ISACTIVER      (GICD_BASE + 0x300)
#define GICD_ICACTIVER      (GICD_BASE + 0x380)
#define GICD_IPRIORITYR     (GICD_BASE + 0x400)
#define GICD_ICFGR          (GICD_BASE + 0xc00)
#define GICD_NSACR          (GICD_BASE + 0xe00)
#define GICD_ITARGETSR      (GICD_BASE + 0x800)
#define GICD_SGIR           (GICD_BASE + 0xF00)
#define GICD_CPENDSGIR      (GICD_BASE + 0xF10)
#define GICD_SPENDSGIR      (GICD_BASE + 0xF20)
#define GICD_PIDR2_GICV2    (GICD_BASE + 0xFE8)

#define GICC_BASE           0xff842000

/* Physical CPU Interface registers */
#define GICC_CTLR       (GICC_BASE + 0x0)
#define GICC_PMR        (GICC_BASE +0x4)
#define GICC_BPR        (GICC_BASE +0x8)
#define GICC_IAR        (GICC_BASE +0xC)
#define GICC_EOIR       (GICC_BASE +0x10)
#define GICC_RPR        (GICC_BASE +0x14)
#define GICC_HPPIR      (GICC_BASE +0x18)
#define GICC_AHPPIR     (GICC_BASE +0x28)
#define GICC_IIDR       (GICC_BASE +0xFC)
#define GICC_DIR        (GICC_BASE +0x1000)
#define GICC_PRIODROP       GICC_EOIR

/* GICC_CTLR bit definitions */
#define EOI_MODE_NS         BIT(10)
#define EOI_MODE_S          BIT(9)
#define IRQ_BYP_DIS_GRP1    BIT(8)
#define FIQ_BYP_DIS_GRP1    BIT(7)
#define IRQ_BYP_DIS_GRP0    BIT(6)
#define FIQ_BYP_DIS_GRP0    BIT(5)
#define CBPR                BIT(4)
#define FIQ_EN_SHIFT        3
#define FIQ_EN_BIT          BIT(FIQ_EN_SHIFT)
#define ACK_CTL             BIT(2)

/* GICD_CTLR bit definitions */
#define CTLR_ENABLE_G0_SHIFT    0
#define CTLR_ENABLE_G0_MASK     (0x1)
#define CTLR_ENABLE_G0_BIT      BIT(CTLR_ENABLE_G0_SHIFT)

void init_gicd()
{
    unsigned int index, count, num_ints;

    put32(GICD_CTLR, 0);

    num_ints = get32(GICD_TYPER);
    num_ints &= TYPER_IT_LINES_NO_MASK;
    num_ints = (num_ints + 1) << 5;
#if 0
    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_ICENABLER + (index << 2), 0xFFFFFFFF);
    }

    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_ICPENDR + (index << 2), 0xFFFFFFFF);
    }
#endif
    count = num_ints >> 2;
    for (index = 0; index < count; index++) {
        put32(GICD_IPRIORITYR + (index << 2), 0);
    }

    count = num_ints >> 2;
    for (index = 0; index < count; index++) {
        put32(GICD_ITARGETSR + (index << 2), 0x01010101);
    }
#if 0
    count = num_ints >> 4;
    for (index = 0; index < count; index++) {
        put32(GICD_ICFGR + (index << 2), 0);
    }
#endif
    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_IGROUPR + (index << 2), 0);
    }

    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_ISENABLER + (index << 2), 0xFFFFFFFF);
    }

    put32(GICD_CTLR, 3);

}

void init_gicc()
{
    uint32_t val = CTLR_ENABLE_G0_BIT | FIQ_EN_BIT | FIQ_BYP_DIS_GRP0;
    val |= IRQ_BYP_DIS_GRP0 | FIQ_BYP_DIS_GRP1 | IRQ_BYP_DIS_GRP1;

    put32(GICC_CTLR, 0);
    put32(GICC_PMR, 0xFF);
    put32(GICC_BPR, 0x7);
    put32(GICC_CTLR, val);

}

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

    enable_irq();
    enable_fiq();

    while (1) {
        if (get32(GICC_IAR) != 1023)
            printf("GICC_HPPIR: %x\n", get32(GICC_IAR));

    }
}