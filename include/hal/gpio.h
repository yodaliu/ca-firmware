#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include "address.h"

#define GPFSEL0         (GPIO_BASE+0x00)
#define GPFSEL1         (GPIO_BASE+0x04)
#define GPFSEL2         (GPIO_BASE+0x08)
#define GPFSEL3         (GPIO_BASE+0x0C)
#define GPFSEL4         (GPIO_BASE+0x10)
#define GPSET0          (GPIO_BASE+0x1C)
#define GPSET1          (GPIO_BASE+0x20)
#define GPCLR0          (GPIO_BASE+0x28)
#define GPCLR1          (GPIO_BASE+0x2C)
#define GPLEV0          (GPIO_BASE+0x34)
#define GPLEV1          (GPIO_BASE+0x38)
#define GPEDS0          (GPIO_BASE+0x40)
#define GPEDS1          (GPIO_BASE+0x44)
#define GPREN0          (GPIO_BASE+0x4C)
#define GPREN1          (GPIO_BASE+0x50)
#define GPFEN0          (GPIO_BASE+0x58)
#define GPFEN1          (GPIO_BASE+0x5C)
#define GPHEN0          (GPIO_BASE+0x64)
#define GPHEN1          (GPIO_BASE+0x68)
#define GPLEN0          (GPIO_BASE+0x70)
#define GPLEN1          (GPIO_BASE+0x74)
#define GPAREN0         (GPIO_BASE+0x7C)
#define GPAREN1         (GPIO_BASE+0x80)
#define GPAFEN0         (GPIO_BASE+0x88)
#define GPAFEN1         (GPIO_BASE+0x8C)
#define GPPUD           (GPIO_BASE+0x94)
#define GPPUDCLK0       (GPIO_BASE+0x98)
#define GPPUDCLK1       (GPIO_BASE+0x9C)

enum DETECT_MODE {
    DETECT_RISING,
    DETECT_FALLING,
    DETECT_HIGH,
    DETECT_LOW,
    DETECT_RISING_ASYNC,
    DETECT_FALLING_ASYNC,
    DETECT_MAX
};

/* GPIO pull up or down states */
enum PULL_STATE {
    PULL_DISABLE,
    PULL_UP,
    PULL_DOWN,
    PULL_RESERVED
};

enum GPIO_MODE {
    GPIO_IN = 0,
    GPIO_OUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2
};

void set_gpio_mode(
    uint32_t pin,
    enum GPIO_MODE mode
);

void set_gpio_level(
    uint32_t pin,
    uint32_t value
);

uint32_t get_gpio_level(
    uint32_t pin
);

void enable_gpio_detect(
    uint32_t pin,
    enum DETECT_MODE type
);

void disable_gpio_detect(
    uint32_t pin,
    enum DETECT_MODE type
);

uint32_t get_gpio_detect(
    uint32_t pin
);

void clear_gpio_detect(
    uint32_t pin
);

#endif //#ifndef _GPIO_H_
