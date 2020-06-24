#include <stdint.h>
#include <hal/gicv2.h>
#include <sys/io.h>
#include <sys/utils.h>

void disabe_intrpt(uint32_t id)
{

    uint32_t group = id >> 5;
    uint32_t offset = id % 32;

    put32(GICD_ICENABLER + (group << 2), (get32(GICD_ICENABLER + (group << 2)) | (1 << offset)));
}


void enable_intrpt(uint32_t id)
{
    uint32_t group = id >> 5;
    uint32_t offset = id % 32;

    put32(GICD_ISENABLER + (group << 2), (get32(GICD_ISENABLER + (group << 2)) | (1 << offset)));
}

void clear_intrpt_pending(uint32_t id)
{

    uint32_t group = id >> 5;
    uint32_t offset = id % 32;

    put32(GICD_ICPENDR + (group << 2), (get32(GICD_ICPENDR + (group << 2)) | (1 << offset)));
}

uint32_t probe_intrpt_pending(uint32_t id)
{

    uint32_t group = id >> 5;
    uint32_t offset = id % 32;
    uint32_t value;

    value = get32(GICD_ISPENDR + (group << 2));
    value &= (1 << offset);

    return (value >> offset);
}

void set_intrpt_prio(uint32_t id, uint8_t prio)
{

    uint32_t group = id >> 2;
    uint32_t offset = (id % 4) << 8;
    uint32_t value;

    value = get32(GICD_IPRIORITYR + (group << 2));
    value &= ~(0xFF << offset);
    value |= (prio & 0xFF) << offset;
    put32(GICD_IPRIORITYR + (group << 2), value);
}

uint8_t get_intrpt_prio(uint32_t id)
{
    uint32_t group = id >> 2;
    uint32_t offset = (id % 4) << 8;
    uint32_t value;

    value = get32(GICD_IPRIORITYR + (group << 2));
    value &= (0xFF << offset);

    return (value >> offset);
}

void init_gicd()
{
    unsigned int index, count, num_ints;

    put32(GICD_CTLR, 0);

    num_ints = get32(GICD_TYPER);
    num_ints &= TYPER_IT_LINES_NO_MASK;
    num_ints = (num_ints + 1) << 5;

    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_ICENABLER + (index << 2), 0xFFFFFFFF);
    }

    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_ICPENDR + (index << 2), 0xFFFFFFFF);
    }

    count = num_ints >> 2;
    for (index = 0; index < count; index++) {
        put32(GICD_IPRIORITYR + (index << 2), 0);
    }

    count = num_ints >> 2;
    for (index = 0; index < count; index++) {
        put32(GICD_ITARGETSR + (index << 2), 0x01010101);
    }

    count = num_ints >> 4;
    for (index = 0; index < count; index++) {
        put32(GICD_ICFGR + (index << 2), 0);
    }

    count = num_ints >> 5;
    for (index = 0; index < count; index++) {
        put32(GICD_IGROUPR + (index << 2), 0);
    }

    put32(GICD_CTLR, 3);

}

void init_gicc()
{
    //uint32_t val = CTLR_ENABLE_G0_BIT | FIQ_EN_BIT | FIQ_BYP_DIS_GRP0;
    uint32_t val = CTLR_ENABLE_G0_BIT | FIQ_BYP_DIS_GRP0;
    val |= IRQ_BYP_DIS_GRP0 | FIQ_BYP_DIS_GRP1 | IRQ_BYP_DIS_GRP1;

    put32(GICC_CTLR, 0);
    put32(GICC_PMR, 0xFF);
    put32(GICC_BPR, 0);
    put32(GICC_CTLR, val);

}