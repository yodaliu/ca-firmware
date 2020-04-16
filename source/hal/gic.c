#include <stdint.h>
#include <sys/io.h>
#include <sys/utils.h>
#include <hal/gic.h>

void disabe_irq_n(uint32_t irq)
{

    uint32_t group = irq / 32;
    uint32_t offset = irq % 32;

    put32(GICD_ICENABLER + (group << 2), (get32(GICD_ICENABLER + (group << 2)) | (1 << offset)));
}


void enable_irq_n(uint32_t irq)
{
    uint32_t group = irq / 32;
    uint32_t offset = irq % 32;

    put32(GICD_ISENABLER + (group << 2), (get32(GICD_ISENABLER + (group << 2)) | (1 << offset)));
}


void end_irq_n(uint32_t irq)
{

    uint32_t group = irq / 32;
    uint32_t offset = irq % 32;

    put32(GICD_ICPENDR + (group << 2), (get32(GICD_ICPENDR + (group << 2)) | (1 << offset)));
}

uint32_t probe_irq_n(uint32_t irq)
{

    uint32_t group = irq / 32;
    uint32_t offset = irq % 32;
    uint32_t value;

    value = get32(GICD_ISPENDR + (group << 2));
    value &= (1 << offset);

    return (value >> offset);
}

void set_irq_prio(uint32_t irq, uint8_t prio)
{

    uint32_t group = irq / 4;
    uint32_t offset = (irq % 4) << 8;
    uint32_t value;

    value = get32(GICD_ISPENDR + (group << 2));
    value &= ~(0xFF << offset);
    value |= (prio & 0xFF) << offset;
    put32(GICD_ISPENDR + (group << 2), value);
}

uint8_t get_irq_prio(uint32_t irq)
{

    uint32_t group = irq / 4;
    uint32_t offset = (irq % 4) << 8;
    uint32_t value;

    value = get32(GICD_ISPENDR + (group << 2));
    value &= (0xFF << offset);

    return (value >> offset);
}

static void init_gicd(void)
{
    unsigned int addr = 0;

    put32(GICD_CTLR, 0);

    // Disable all interrupts
    addr = GICD_ICENABLER;
    while (addr < GICD_ICENABLERN) {
        put32(addr, 0xFFFFFFFF);
        addr += 4;
    }

    // Clear all pending interrupts
    addr = GICD_ICPENDR;
    while (addr < GICD_ICPENDRN) {
        put32(addr, 0xFFFFFFFF);
        addr += 4;
    }

    // Set all interrupt to the lowest prio.
    addr = GICD_IPRIORITYR;
    while (addr < GICD_IPRIORITYRN) {
        put32(addr, 0xFFFFFFFF);
        addr += 4;
    }

    // Set all interrupt to group 0
    addr = GICD_IGROUPR;
    while (addr < GICD_IGROUPRN) {
        put32(addr, 0);
        addr += 4;
    }

    // Set all interrupt to level sensitive
    addr = GICD_ICFGR;
    while (addr < GICD_ICFGRN) {
        put32(addr, 0xFFFFFFFF);
        addr += 4;
    }

    // Set all interrupt targets to CPU0
    addr = GICD_ITARGETSR;
    while (addr < GICD_ITARGETSRN) {
        put32(addr, 0);
        addr += 4;
    }

    // Enable group 0 interrupts
    put32(GICD_CTLR, 1);
}

static void init_gicc(void)
{

    uint32_t value;

    put32(GICC_CTLR, 0);

    // Unmask all interrupts
    put32(GICC_PMR, 0xFF);

    // All interrupts in single group
    put32(GICC_BPR, 0);

    // End all pending interrupts
    value = get32(GICC_IAR) & 0x3FF;

    while ((value != 1023) | (value != 1022)) {
        put32(GICC_EOIR, get32(GICC_IAR));
        value = get32(GICC_IAR) & 0x3FF;
    }

    // Enable group 0 interrupts
    put32(GICC_CTLR, 1);

}

void init_gic(void)
{
    init_gicd();
    init_gicc();
}
