#ifndef _GICV2_H_
#define _GICV2_H_

#include <stdint.h>
#include "address.h"
#include "../sys/utils.h"

#define MIN_SGI_ID                  (0)
#define MIN_SEC_SGI_ID              (8)
#define MIN_PPI_ID                  (16)
#define MIN_SPI_ID                  (32)
#define MAX_SPI_ID                  (1019)

#define TOTAL_SPI_INTR_NUM  (MAX_SPI_ID - MIN_SPI_ID + (1))
#define TOTAL_PCPU_INTR_NUM (MIN_SPI_ID - MIN_SGI_ID)

/* Highest possible interrupt priorities */
#define GIC_HIGHEST_SEC_PRIORITY    (0x00)
#define GIC_HIGHEST_NS_PRIORITY     (0x80)

/* GICD_TYPER shifts and masks */
#define TYPER_IT_LINES_NO_SHIFT     (0)
#define TYPER_IT_LINES_NO_MASK      (0x1f)

#define GICD_BASE                   0xff841000

#define GICD_CTLR                   (GICD_BASE + 0x0)
#define GICD_TYPER                  (GICD_BASE + 0x4)
#define GICD_IIDR                   (GICD_BASE + 0x8)
#define GICD_IGROUPR                (GICD_BASE + 0x80)
#define GICD_ISENABLER              (GICD_BASE + 0x100)
#define GICD_ICENABLER              (GICD_BASE + 0x180)
#define GICD_ISPENDR                (GICD_BASE + 0x200)
#define GICD_ICPENDR                (GICD_BASE + 0x280)
#define GICD_ISACTIVER              (GICD_BASE + 0x300)
#define GICD_ICACTIVER              (GICD_BASE + 0x380)
#define GICD_IPRIORITYR             (GICD_BASE + 0x400)
#define GICD_ICFGR                  (GICD_BASE + 0xc00)
#define GICD_NSACR                  (GICD_BASE + 0xe00)
#define GICD_ITARGETSR              (GICD_BASE + 0x800)
#define GICD_SGIR                   (GICD_BASE + 0xF00)
#define GICD_CPENDSGIR              (GICD_BASE + 0xF10)
#define GICD_SPENDSGIR              (GICD_BASE + 0xF20)
#define GICD_PIDR2_GICV2            (GICD_BASE + 0xFE8)

#define GICC_BASE                   0xff842000

/* Physical CPU Interface registers */
#define GICC_CTLR                   (GICC_BASE + 0x0)
#define GICC_PMR                    (GICC_BASE +0x4)
#define GICC_BPR                    (GICC_BASE +0x8)
#define GICC_IAR                    (GICC_BASE +0xC)
#define GICC_EOIR                   (GICC_BASE +0x10)
#define GICC_RPR                    (GICC_BASE +0x14)
#define GICC_HPPIR                  (GICC_BASE +0x18)
#define GICC_AHPPIR                 (GICC_BASE +0x28)
#define GICC_IIDR                   (GICC_BASE +0xFC)
#define GICC_DIR                    (GICC_BASE +0x1000)
#define GICC_PRIODROP               GICC_EOIR

/* GICC_CTLR bit definitions */
#define EOI_MODE_NS                 BIT(10)
#define EOI_MODE_S                  BIT(9)
#define IRQ_BYP_DIS_GRP1            BIT(8)
#define FIQ_BYP_DIS_GRP1            BIT(7)
#define IRQ_BYP_DIS_GRP0            BIT(6)
#define FIQ_BYP_DIS_GRP0            BIT(5)
#define CBPR                        BIT(4)
#define FIQ_EN_SHIFT                3
#define FIQ_EN_BIT                  BIT(FIQ_EN_SHIFT)
#define ACK_CTL                     BIT(2)

/* GICD_CTLR bit definitions */
#define CTLR_ENABLE_G0_SHIFT        0
#define CTLR_ENABLE_G0_MASK         (0x1)
#define CTLR_ENABLE_G0_BIT          BIT(CTLR_ENABLE_G0_SHIFT)

/* PPI */
#define GIC_ARM_IRQ_HP_TIMER        26
#define GIC_ARM_IRQ_V_TIMER         27
#define GIC_ARM_IRQ_LEGACY_FIQ      28
#define GIC_ARM_IRQ_PS_TIMER        29
#define GIC_ARM_IRQ_PNS_TIMER       30
#define GIC_ARM_IRQ_LEGACY_IRQ      31

/* SPI */
#define GIC_ARM_LOCAL_IRQ_CORE0_PMU 48
#define GIC_ARM_LOCAL_IRQ_CORE1_PMU 49
#define GIC_ARM_LOCAL_IRQ_CORE2_PMU 50
#define GIC_ARM_LOCAL_IRQ_CORE3_PMU 51
#define GIC_ARM_LOCAL_IRQ_AXI_ERR   52
#define GIC_ARM_LOCAL_IRQ_TIMER     53
#define GIC_ARMC_IRQ_TIMER          64
#define GIC_ARMC_IRQ_MAILBOX        65
#define GIC_ARMC_IRQ_DOORBELL0      66
#define GIC_ARMC_IRQ_DOORBELL1      67
#define GIC_ARMC_IRQ_VPU0_HALTED    68
#define GIC_ARMC_IRQ_VPU1_HALTED    69
#define GIC_ARMC_IRQ_ARM_ADDR_ERR   70
#define GIC_ARMC_IRQ_ARM_AXI_ERR    71
#define GIC_ARMC_IRQ_SWI0           72
#define GIC_ARMC_IRQ_SWI1           73
#define GIC_ARMC_IRQ_SWI2           74
#define GIC_ARMC_IRQ_SWI3           75
#define GIC_ARMC_IRQ_SWI4           76
#define GIC_ARMC_IRQ_SWI5           77
#define GIC_ARMC_IRQ_SWI6           78
#define GIC_ARMC_IRQ_SWI7           79
#define GIC_VC_IRQ_TIMER0           96
#define GIC_VC_IRQ_TIMER1           97
#define GIC_VC_IRQ_TIMER2           98
#define GIC_VC_IRQ_TIMER3           99
#define GIC_VC_IRQ_DMA0             112
#define GIC_VC_IRQ_DMA1             113
#define GIC_VC_IRQ_DMA2             114
#define GIC_VC_IRQ_DMA3             115
#define GIC_VC_IRQ_DMA4             116
#define GIC_VC_IRQ_DMA5             117
#define GIC_VC_IRQ_DMA6             118
#define GIC_VC_IRQ_DMA7_8           119
#define GIC_VC_IRQ_DMA9_10          120
#define GIC_VC_IRQ_DMA11            121
#define GIC_VC_IRQ_DMA12            122
#define GIC_VC_IRQ_DMA13            123
#define GIC_VC_IRQ_DMA14            124
#define GIC_VC_IRQ_AUX              125
#define GIC_VC_IRQ_DMA15            127
#define GIC_VC_IRQ_GPIO0            145
#define GIC_VC_IRQ_GPIO1            146
#define GIC_VC_IRQ_GPIO2            147
#define GIC_VC_IRQ_GPIO3            148
#define GIC_VC_IRQ_I2C              149
#define GIC_VC_IRQ_SPI              150
#define GIC_VC_IRQ_UART             153

void disabe_intrpt(
    uint32_t irq
);

void enable_intrpt(
    uint32_t irq
);

void clear_intrpt_pending(
    uint32_t irq
);

uint32_t probe_intrpt_pending(
    uint32_t irq
);

void set_intrpt_prio(
    uint32_t irq,
    uint8_t prio
);

uint8_t get_intrpt_prio(
    uint32_t irq
);

void init_gicd(
    void
);

void init_gicc(
    void
);

#endif //#ifndef _GICV2_H_
