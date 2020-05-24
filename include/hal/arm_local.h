#ifndef _ARM_LOCAL_H_
#define _ARM_LOCAL_H_

#include <stdint.h>
#include "address.h"
#include "../sys/utils.h"

#define ARM_LOCAL_ARM_CONTROL           (ARM_LOCAL_BASE + 0x00)
#define AXIERRIRQ_MASK                  BIT(0)

#define ARM_LOCAL_CORE_IRQ_CONTROL      (ARM_LOCAL_BASE + 0x0C)
#define AXI_ERR_CORE_SH                 4
#define AXI_ERR_CORE_MSK                0x7

#define ARM_LOCAL_PMU_CONTROL_SET       (ARM_LOCAL_BASE + 0x10)
#define ARM_LOCAL_PMU_CONTROL_CLR       (ARM_LOCAL_BASE + 0x14)
#define PMU_FIQ_SH                      4
#define PMU_FIQ_MSK                     0xf
#define PMU_IRQ_SH                      0
#define PMU_IRQ_MSK                     0xf

#define ARM_LOCAL_PERI_IRQ_ROUTE0       (ARM_LOCAL_BASE + 0x24)
#define WRITE_MASKS_SH                  24
#define WRITE_MASKS_MSK                 0xff
#define LOCAL_TIMER_IRQ_SH              0
#define LOCAL_TIMER_IRQ_MSK             0x7

#define ARM_LOCAL_AXI_QUIET_TIME        (ARM_LOCAL_BASE + 0x30)
#define AXI_QUIET_IRQ_ENB               BIT(20)
#define AXI_QUIET_TIME_SH               0
#define AXI_QUIET_TIME_MSK              0xfffff

#define ARM_LOCAL_LOCAL_TIMER_CONTROL   (ARM_LOCAL_BASE + 0x34)
#define TIMER_IRQ_FLAG                  BIT(31)
#define TIMER_IRQ_EN                    BIT(29)
#define TIMER_EN                        BIT(28)
#define TIMER_TIMEOUT_SH                0
#define ATIMER_TIMEOUT_MSK              0xfffffff

#define ARM_LOCAL_LOCAL_TIMER_IRQ       (ARM_LOCAL_BASE + 0x38)
#define IRQ_CLEAR                       BIT(31)
#define RELOAD                          BIT(30)

#define ARM_LOCAL_TIMER_CNTRL0          (ARM_LOCAL_BASE + 0x40)
#define ARM_LOCAL_TIMER_CNTRL1          (ARM_LOCAL_BASE + 0x44)
#define ARM_LOCAL_TIMER_CNTRL2          (ARM_LOCAL_BASE + 0x48)
#define ARM_LOCAL_TIMER_CNTRL3          (ARM_LOCAL_BASE + 0x4C)
#define CNT_V_IRQ_FIQ                   BIT(7)
#define CNT_HP_IRQ_FIQ                  BIT(6)
#define CNT_PNS_IRQ_FIQ                 BIT(5)
#define CNT_PS_IRQ_FIQ                  BIT(4)
#define CNT_V_IRQ                       BIT(3)
#define CNT_HP_IRQ                      BIT(2)
#define CNT_PNS_IRQ                     BIT(1)
#define CNT_PS_IRQ                      BIT(0)

#define ARM_LOCAL_MAILBOX_CNTRL0        (ARM_LOCAL_BASE + 0x50)
#define ARM_LOCAL_MAILBOX_CNTRL1        (ARM_LOCAL_BASE + 0x54)
#define ARM_LOCAL_MAILBOX_CNTRL2        (ARM_LOCAL_BASE + 0x58)
#define ARM_LOCAL_MAILBOX_CNTRL3        (ARM_LOCAL_BASE + 0x5C)
#define MBOX3_FIQ                       BIT(7)
#define MBOX2_FIQ                       BIT(6)
#define MBOX1_FIQ                       BIT(5)
#define MBOX0_FIQ                       BIT(4)
#define MBOX3_IRQ                       BIT(3)
#define MBOX2_IRQ                       BIT(2)
#define MBOX1_IRQ                       BIT(1)
#define MBOX0_IRQ                       BIT(0)

#define ARM_LOCAL_IRQ_SOURCE0           (ARM_LOCAL_BASE + 0x60)
#define ARM_LOCAL_IRQ_SOURCE1           (ARM_LOCAL_BASE + 0x64)
#define ARM_LOCAL_IRQ_SOURCE2           (ARM_LOCAL_BASE + 0x68)
#define ARM_LOCAL_IRQ_SOURCE3           (ARM_LOCAL_BASE + 0x6C)
#define ARM_LOCAL_FIQ_SOURCE0           (ARM_LOCAL_BASE + 0x70)
#define ARM_LOCAL_FIQ_SOURCE1           (ARM_LOCAL_BASE + 0x74)
#define ARM_LOCAL_FIQ_SOURCE2           (ARM_LOCAL_BASE + 0x78)
#define ARM_LOCAL_FIQ_SOURCE3           (ARM_LOCAL_BASE + 0x7C)
#define AXI_ERR_FIQ_IRQ                 BIT(30)
#define LOCAL_TIMER_FIQ_IRQ             BIT(11)
#define AXI_QUIET_IRQ                   BIT(10)
#define PMU_FIQ_IRQ                     BIT(9)
#define VC_FIQ_IRQ                      BIT(8)
#define MAILBOX_FIQ_IRQ_SH              4
#define MAILBOX_FIQ_IRQ_MSK             0xf
#define CNT_V_FIQ_IRQ                   BIT(3)
#define CNT_HP_FIQ_IRQ                  BIT(2)
#define CNT_PNS_FIQ_IRQ                 BIT(1)
#define CNT_PS_FIQ_IRQ                  BIT(0)

#endif //#ifndef _ARM_LOCAL_H_