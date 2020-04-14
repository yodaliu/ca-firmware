#ifndef _GIC_H_
#define _GIC_H_

#include <stdint.h>
#include "address.h"

#define GICD_BASE   		(ARM_LOCAL_BASE + 41000)
#define GICC_BASE   		(ARM_LOCAL_BASE + 42000)

#define GICD_CTLR           (GICD_BASE + 0x000)
#define GICD_TYPER          (GICD_BASE + 0x004)
#define GICD_IIDR           (GICD_BASE + 0x008)
#define GICD_IGROUPR        (GICD_BASE + 0x080)
#define GICD_IGROUPRN       (GICD_BASE + 0x0FC)
#define GICD_ISENABLER      (GICD_BASE + 0x100)
#define GICD_ISENABLERN     (GICD_BASE + 0x17C)
#define GICD_ICENABLER      (GICD_BASE + 0x180)
#define GICD_ICENABLERN     (GICD_BASE + 0x1FC)
#define GICD_ISPENDR        (GICD_BASE + 0x200)
#define GICD_ISPENDRN       (GICD_BASE + 0x27C)
#define GICD_ICPENDR        (GICD_BASE + 0x280)
#define GICD_ICPENDRN       (GICD_BASE + 0x2FC)
#define GICD_ISACTIVER      (GICD_BASE + 0x300)
#define GICD_ISACTIVERN     (GICD_BASE + 0x37C)
#define GICD_ICACTIVER      (GICD_BASE + 0x380)
#define GICD_ICACTIVERN     (GICD_BASE + 0x3FC)
#define GICD_IPRIORITYR     (GICD_BASE + 0x400)
#define GICD_IPRIORITYRN    (GICD_BASE + 0x7F8)
#define GICD_ITARGETSR      (GICD_BASE + 0x800)
#define GICD_ITARGETSRN     (GICD_BASE + 0xBF8)
#define GICD_ICFGR          (GICD_BASE + 0xC00)
#define GICD_ICFGRN         (GICD_BASE + 0xCFC)
#define GICD_NSACR          (GICD_BASE + 0xE00)
#define GICD_NSACRN         (GICD_BASE + 0xEFC)
#define GICD_SGIR           (GICD_BASE + 0xF00)
#define GICD_CPENDSGIR      (GICD_BASE + 0xF10)
#define GICD_CPENDSGIRN     (GICD_BASE + 0xF1C)
#define GICD_SPENDSGIR      (GICD_BASE + 0xF20)
#define GICD_SPENDSGIRN     (GICD_BASE + 0xF2C)
#define GICD_ICPIDR2        (GICD_BASE + 0xFE8)

#define GICD_SGI_TARGET_LIST_SHIFT   (24)
#define GICD_SGI_TARGET_LIST_MASK    (0x3UL << GICD_SGI_TARGET_LIST_SHIFT)
#define GICD_SGI_TARGET_LIST         (0UL<<GICD_SGI_TARGET_LIST_SHIFT)
#define GICD_SGI_TARGET_LIST_VAL     (0)
#define GICD_SGI_TARGET_OTHERS       (1UL<<GICD_SGI_TARGET_LIST_SHIFT)
#define GICD_SGI_TARGET_OTHERS_VAL   (1)
#define GICD_SGI_TARGET_SELF         (2UL<<GICD_SGI_TARGET_LIST_SHIFT)
#define GICD_SGI_TARGET_SELF_VAL     (2)
#define GICD_SGI_TARGET_SHIFT        (16)
#define GICD_SGI_TARGET_MASK         (0xFFUL<<GICD_SGI_TARGET_SHIFT)
#define GICD_SGI_GROUP1              (1UL<<15)
#define GICD_SGI_INTID_MASK          (0xFUL)

#define GICC_CTLR       (GICC_BASE + 0x0000)
#define GICC_PMR        (GICC_BASE + 0x0004)
#define GICC_BPR        (GICC_BASE + 0x0008)
#define GICC_IAR        (GICC_BASE + 0x000C)
#define GICC_EOIR       (GICC_BASE + 0x0010)
#define GICC_RPR        (GICC_BASE + 0x0014)
#define GICC_HPPIR      (GICC_BASE + 0x0018)
#define GICC_APR        (GICC_BASE + 0x00D0)
#define GICC_NSAPR      (GICC_BASE + 0x00E0)
#define GICC_DIR        (GICC_BASE + 0x1000)

/* Register bits */
#define GICD_CTL_ENABLE 		0x1

#define GICD_TYPE_LINES 		0x01f
#define GICD_TYPE_CPUS_SHIFT 	5
#define GICD_TYPE_CPUS  		0x0e0
#define GICD_TYPE_SEC   		0x400

#define GICC_CTL_ENABLE 		0x1
#define GICC_CTL_EOI    		(0x1 << 9)

#define GICC_IA_IRQ       		0x03ff
#define GICC_IA_CPU_MASK  		0x1c00
#define GICC_IA_CPU_SHIFT 		10

/* SPI */
#define GIC_ARM_CORE0_PMU			48
#define GIC_ARM_CORE1_PMU			49
#define GIC_ARM_CORE2_PMU			50
#define GIC_ARM_CORE3_PMU			51
#define GIC_ARM_LOCAL_IRQ_AXI_ERR	52
#define GIC_ARM_LOCAL_IRQ_TIMER		53
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

#ifndef __ASSEMBLY__

void disabe_irq_n(
	uint32_t irq
);

void enable_irq_n(
	uint32_t irq
);

void end_irq_n(
	uint32_t irq
);

uint32_t probe_irq_n(
	uint32_t irq
);

void set_irq_prio(
	uint32_t irq,
	uint8_t prio
);

uint8_t get_irq_prio(
	uint32_t irq
);

void init_interrupt(
	void
);

#endif //#ifndef __ASSEMBLY__
#endif //#ifndef _GIC_H_
