#include <sys/utils.h>

#define LOCAL_CONTROL	0xff800000
#define LOCAL_PRESCALER	0xff800008
#define GIC_DISTB		0xff841000
#define GIC_CPUB		0xff842000

#define OSC_FREQ		54000000

#define SCR_RW			BIT(10)
#define SCR_HCE			BIT(8)
#define SCR_SMD			BIT(7)
#define SCR_RES1_5		BIT(5)
#define SCR_RES1_4		BIT(4)
#define SCR_EA			BIT(3)
#define SCR_FIQ			BIT(2)
#define SCR_IRQ			BIT(1)
#define SCR_NS			BIT(0)
#define SCR_VAL			(SCR_RW | SCR_HCE | SCR_SMD | SCR_RES1_5 | SCR_RES1_4 | SCR_NS | SCR_EA | SCR_FIQ | SCR_IRQ)

#define CPUECTLR_EL1		S3_1_C15_C2_1
#define CPUECTLR_EL1_SMPEN	BIT(6)

#define SPSR_EL3_D		BIT(9)
#define SPSR_EL3_A		BIT(8)
#define SPSR_EL3_I		BIT(7)
#define SPSR_EL3_F		BIT(6)
#define SPSR_EL3_MODE_EL2H	9
#define SPSR_EL3_VAL	(SPSR_EL3_D | SPSR_EL3_A | SPSR_EL3_I | SPSR_EL3_F | SPSR_EL3_MODE_EL2H)

#define L2CTLR_EL1		S3_1_C11_C0_2

#define GICC_CTRLR		0x0
#define GICC_PMR		0x4
#define IT_NR			0x8	// Number of interrupt enable registers (256 total irqs)
#define GICD_CTRLR		0x0
#define GICD_IGROUPR	0x80

#define PAGE_SHIFT      12
#define TABLE_SHIFT     9
#define SECTION_SHIFT   (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE       (1 << PAGE_SHIFT)
#define SECTION_SIZE    (1 << SECTION_SHIFT)

#define LOW_MEMORY      (2 * SECTION_SIZE)


.section ".text.boot"

.globl _start
_start:
/*
	 * LOCAL_CONTROL:
	 * Bit 9 clear: Increment by 1 (vs. 2).
	 * Bit 8 clear: Timer source is 19.2MHz crystal (vs. APB).
	 */
	mov x0, LOCAL_CONTROL
	str wzr, [x0]
	/* LOCAL_PRESCALER; divide-by (0x80000000 / register_val) == 1 */
	mov w1, 0x80000000
	str w1, [x0, #(LOCAL_PRESCALER - LOCAL_CONTROL)]

	/* Set L2 read/write cache latency to 3 */
	mrs x0, L2CTLR_EL1
	mov x1, #0x22
	orr x0, x0, x1
	msr L2CTLR_EL1, x0

	/* Set up CNTFRQ_EL0 */
	ldr x0, =OSC_FREQ
	msr CNTFRQ_EL0, x0

	/* Set up CNTVOFF_EL2 */
	msr CNTVOFF_EL2, xzr

	/* Enable FP/SIMD */
	/* All set bits below are res1; bit 10 (TFP) is set to 0 */
	mov x0, #0x33ff
	msr CPTR_EL3, x0

	/* Set up SCR */
	mov x0, #SCR_VAL
	msr SCR_EL3, x0

	/* Set SMPEN */
	mov x0, #CPUECTLR_EL1_SMPEN
	msr CPUECTLR_EL1, x0

	adr	x0, vectors
	msr	vbar_el3, x0
	isb

	mrs x0, MPIDR_EL1
	and x0, x0, #0xFF
	cbz x0, primary_cpu

proc_hang:
	b 	proc_hang

primary_cpu:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY
	bl	main
	b 	proc_hang		// should never come here

.globl memzero
memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt memzero
	ret
