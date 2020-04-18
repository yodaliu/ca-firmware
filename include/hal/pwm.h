#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>
#include "address.h"
#include "../sys/utils.h"

struct pwm_register {
#define PWM_CTL_MSEN2 BIT(15)
#define PWM_CTL_USEF2 BIT(13)
#define PWM_CTL_POLA2 BIT(12)
#define PWM_CTL_SBIT2 BIT(11)
#define PWM_CTL_RPTL2 BIT(10)
#define PWM_CTL_MODE2 BIT(9)
#define PWM_CTL_PWEN2 BIT(8)
#define PWM_CTL_MSEN1 BIT(7)
#define PWM_CTL_CLRF BIT(6)
#define PWM_CTL_USEF1 BIT(5)
#define PWM_CTL_POLA1 BIT(4)
#define PWM_CTL_SBIT1 BIT(3)
#define PWM_CTL_RPTL1 BIT(2)
#define PWM_CTL_MODE1 BIT(1)
#define PWM_CTL_PWEN1 BIT(0)
    uint32_t CTL;
#define PWM_STA_STA2 BIT(10)
#define PWM_STA_STA1 BIT(9)
#define PWM_STA_BERR BIT(8)
#define PWM_STA_GAPO2 BIT(5)
#define PWM_STA_GAPO1 BIT(4)
#define PWM_STA_RERR1 BIT(3)
#define PWM_STA_WERR1 BIT(2)
#define PWM_STA_EMPT1 BIT(1)
#define PWM_STA_FULL1 BIT(0)
    uint32_t STA;
#define PWM_DMAC_ENAB BIT(31)
#define PWM_DMAC_PANIC_MSK 0xff
#define PWM_DMAC_PANIC_SH 8
#define PWM_DMAC_DREQ_MSK 0xff
#define PWM_DMAC_DREQ_SH 0
    uint32_t DMAC;
    uint32_t RSVD0;
    uint32_t RNG1;
    uint32_t DAT1;
    uint32_t FIF1;
    uint32_t RSVD1;
    uint32_t RNG2;
    uint32_t DAT2;
};

#endif //#ifndef _PWM_H_