#ifndef _MBOX_H_
#define _MBOX_H_

#include <stdint.h>
#include "address.h"

extern volatile uint32_t mbox[36];

#define MBOX_REQUEST    0
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_GETSERIAL      0x10004
#define MBOX_TAG_SETCLKRATE     0x38002
#define MBOX_TAG_LAST           0

#define VC_MBOX_READ            (VC_MBOX_BASE + 0x00)
#define VC_MBOX_PEEK            (VC_MBOX_BASE + 0x10)
#define VC_MBOX_SENDER          (VC_MBOX_BASE + 0x14)
#define VC_MBOX_STATUS          (VC_MBOX_BASE + 0x18)
#define VC_MBOX_CONFIG          (VC_MBOX_BASE + 0x1C)
#define VC_MBOX_WRITE           (VC_MBOX_BASE + 0x20)

int mbox_call(
    unsigned char ch
);

#endif //#ifndef _MBOX_H_
