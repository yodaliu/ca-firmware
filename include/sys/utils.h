#ifndef _UTILS_H_
#define _UTILS_H_

#define BIT(x) (1 << (x))

#ifndef __ASSEMBLY__

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

void delay(
    uint64_t period
);

int sprintf(
    char *out,
    const char *format, ...
);

int snprintf(
    char *out,
    size_t size,
    const char *format, ...
);

int printf(
    const char *format, ...
);

char *strcpy(
    char *destination,
    const char *source
);

size_t strlen(
    const char *str
);

void *memset(
    void *s,
    int c,
    size_t sz
);

void *memcpy(
    void *dest,
    const void *src,
    size_t n
);

void *memmove(
    void *dest,
    const void *src,
    size_t n
);

int memcmp(
    const void *str1,
    const void *str2,
    size_t count
);

#endif //#ifndef __ASSEMBLY__
#endif //#ifndef _UTILS_H_
