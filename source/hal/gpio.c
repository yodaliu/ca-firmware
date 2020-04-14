#include <stdint.h>
#include <sys/io.h>
#include <sys/utils.h>
#include <hal/gpio.h>

void set_gpio_mode(uint32_t pin, enum GPIO_MODE mode)
{
    uint32_t group = pin / 10;
    uint32_t offset = (pin % 10) * 3;
    uint32_t registers[5] = { GPFSEL0, GPFSEL1, GPFSEL2, GPFSEL3, GPFSEL4 };

    uint32_t value = get32(registers[group]);

    value &= ~(0x7 << offset);
    value |= ((mode & 0x7) << offset);
    put32(registers[group], value);
}

void set_gpio_level(uint32_t pin, uint32_t level)
{
    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;
    uint32_t setregs[2] = { GPSET0, GPSET1};
    uint32_t clrregs[2] = { GPCLR0, GPCLR1};
    uint32_t mask;

    mask = (!!level) << offset;

    if (!!level) {
        put32(setregs[group], get32(setregs[group]) | mask);
    } else {
        put32(clrregs[group], get32(clrregs[group]) | mask);
    }
}

uint32_t get_gpio_level(uint32_t pin)
{
    uint32_t registers[2] = { GPLEV0, GPLEV1};
    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;

    return ((get32(registers[group]) >> offset) & 1);
}

void enable_gpio_detect(uint32_t pin, enum DETECT_MODE mode)
{
    uint32_t registers[2][DETECT_MAX] = {
        {GPREN0, GPFEN0, GPHEN0, GPLEN0, GPAREN0, GPAFEN0},
        {GPREN1, GPFEN1, GPHEN1, GPLEN1, GPAREN1, GPAFEN1}
    };

    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;
    uint32_t mask = 1 << offset;
    uint32_t value;

    value = get32(registers[group][mode]) | mask;
    put32(registers[group][mode], value);
}

void disable_gpio_detect(uint32_t pin, enum DETECT_MODE mode)
{
    uint32_t registers[2][DETECT_MAX] = {
        {GPREN0, GPFEN0, GPHEN0, GPLEN0, GPAREN0, GPAFEN0},
        {GPREN1, GPFEN1, GPHEN1, GPLEN1, GPAREN1, GPAFEN1}
    };

    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;
    uint32_t mask = 1 << offset;
    uint32_t value;

    value = get32(registers[group][mode]) & ~mask;
    put32(registers[group][mode], value);
}

uint32_t get_gpio_detect(uint32_t pin)
{
    uint32_t registers[2] = {
        GPEDS0, GPEDS1
    };

    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;

    return ((get32(registers[group]) >> offset) & 1);
}

void clear_gpio_detect(uint32_t pin)
{
    uint32_t registers[2] = {
        GPEDS0, GPEDS1
    };

    uint32_t group = pin / 32;
    uint32_t offset = pin % 32;
    uint32_t value;

    value = get32(registers[group]) | (1 << offset);

    put32(registers[group], value);
}
