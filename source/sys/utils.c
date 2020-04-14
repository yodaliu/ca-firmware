#include <stdint.h>
#include <sys/utils.h>
#include <hal/auxi.h>

void delay(uint64_t period)
{
    volatile uint64_t count = period;
    while (count) {
        count--;
    }
}

static int vsprintf(char *buf, const char *fmt, va_list param)
{
    char *s;
    unsigned int t;
    int count, shift;
    char buffer[40];

    if (buf == NULL) {
        return -1;
    }

    s = buf;
    for (; *fmt != '\0'; ++fmt) {
        if (*fmt != '%') {

            if (*fmt == '\n') {
                *s++ = 0x0D;
                *s++ = 0x0A;
                continue;
            } else {
                *s++ = *fmt;
                continue;
            }
        } else {
            fmt++;
            if ((*fmt == 'x') || (*fmt == 'X')) {
                *s++ = '0';
                *s++ = 'x';
                shift = 28;
                unsigned int hex = va_arg(param, unsigned int);
                unsigned int ncase = (*fmt & 0x20);

                for (; shift >= 0; shift -= 4) {
                    *s++ = "0123456789ABCDEF"[(hex >> shift) & 0xF] | ncase;
                }
            } else if ((*fmt == 'l') && (*(fmt + 1) == 'u')) {
                count = 0;
                unsigned long luvalue = va_arg(param, unsigned long);
                while (luvalue >= 10) {
                    t = luvalue % 10;
                    buffer[count] = t + '0';
                    luvalue /= 10;
                    count++;
                }
                t = luvalue % 10;
                *s++ = t + '0';
                count--;
                while (count >= 0) {
                    *s++ = buffer[count--];
                }
            } else if (*fmt == 'c') {
                char ch = (char)va_arg(param, int);
                *s++ = ch;
            } else {
                *s++ = *fmt;
            }
        }
    }

    *s = '\0';

    return ((s - buf) - 1);
}

static int vsnprintf(char *buf, size_t size, const char *fmt, va_list param)
{
    char *s, *p;
    unsigned int t;
    int count, shift;
    char buffer[40];
    size_t char_count = 0;
    int write_flag = 1;

    if ((size == 0) || (buf == NULL)) {
        write_flag = 0;
    }

    s = buf;
    for (; *fmt != '\0'; ++fmt) {
        if (*fmt != '%') {
            if (*fmt == '\n') {
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = 0x0D;
                }
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = 0x0A;
                }
                continue;
            } else {
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = *fmt;
                }
                continue;
            }
        } else {
            fmt++;
            if ((*fmt == 'l') && (*(fmt + 1) == 'u')) {
                fmt++;
                count = 0;
                unsigned long luvalue = va_arg(param, unsigned long);
                while (luvalue >= 10) {
                    t = luvalue % 10;
                    buffer[count] = t + '0';
                    luvalue /= 10;
                    count++;
                }
                t = luvalue % 10;
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = t + '0';
                }
                count--;
                while (count >= 0) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = buffer[count];
                    }
                    count--;
                }
            } else if ((*fmt == 'l') && (*(fmt + 1) == 'd')) {
                count = 0;
                long lvalue = va_arg(param, long);
                if (lvalue < 0) {
                    lvalue = -lvalue;
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = '-';
                    }
                }
                while (lvalue >= 10) {
                    t = lvalue % 10;
                    buffer[count] = t + '0';
                    lvalue /= 10;
                    count++;
                }
                t = lvalue % 10;
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = t + '0';
                }
                count--;
                while (count >= 0) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = buffer[count];
                    }
                    count--;
                }
            } else if ((*fmt == 'x') || (*fmt == 'X')) {
                char_count++;
                unsigned int hex = va_arg(param, unsigned int);
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = '0';
                }
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = 'x';
                }
                shift = 28;
                unsigned int ncase = (*fmt & 0x20);
                for (; shift >= 0; shift -= 4) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = "0123456789ABCDEF"[(hex >> shift) & 0xF] | ncase;
                    }
                }
            } else if ((*fmt == 'u')) {
                count = 0;
                unsigned int uvalue = va_arg(param, unsigned int);
                while (uvalue >= 10) {
                    t = uvalue % 10;
                    buffer[count] = t + '0';
                    uvalue /= 10;
                    count++;
                }
                t = uvalue % 10;
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = t + '0';
                }
                count--;
                while (count >= 0) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = buffer[count];
                    }
                    count--;
                }
            } else if ((*fmt == 'd')) {
                count = 0;
                int value = va_arg(param, int);
                if (value < 0) {
                    value = -value;
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = '-';
                    }
                }
                while (value >= 10) {
                    t = value % 10;
                    buffer[count] = t + '0';
                    value /= 10;
                    count++;
                }
                t = value % 10;
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = t + '0';
                }
                count--;
                while (count >= 0) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = buffer[count];
                    }
                    count--;
                }
            } else if (*fmt == 'c') {
                char ch = (char)va_arg(param, int);
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = ch;
                }
            } else if (*fmt == 's') {
                char *name = va_arg(param, char *);
                for (p = (char *)name++; *p != '\0'; p++) {
                    char_count++;
                    if ((char_count < size) && (write_flag == 1)) {
                        *s++ = *p;
                    }
                }
            } else {
                char_count++;
                if ((char_count < size) && (write_flag == 1)) {
                    *s++ = *fmt;
                }
            }
        }
    }

    if (s != NULL)
        *s = '\0';

    return char_count;
}

int sprintf(char *out, const char *format, ...)
{
    int length;
    va_list ap;

    va_start(ap, format);

    length = vsprintf(out, format, ap);

    va_end(ap);

    return length;
}

int snprintf(char *out, size_t size, const char *format, ...)
{
    int length;
    va_list ap;

    va_start(ap, format);

    length = vsnprintf(out, size, format, ap);

    va_end(ap);

    return length;
}

static char OSPrintBuffer[1024];

int printf(const char *format, ...)
{
    int length, i;
    va_list ap;

    va_start(ap, format);

    length = vsnprintf(OSPrintBuffer, 1024, format, ap);
    for (i = 0; i < length; i++) {
        uart_send(OSPrintBuffer[i]);
    }

    va_end(ap);

    return length;
}

char *strcpy(char *destination, const char *source)
{
    char *start = destination;

    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}

size_t strlen(const char *str)
{
    int len = 0;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        len++;
    }
    return (len);
}

void *memset(void *s, int c, size_t sz)
{
    unsigned char *p = (unsigned char *)s;

    /* c should only be a byte's worth of information anyway, but let's mask out
    * everything else just in case.
    */
    unsigned char x = c & 0xff;

    while (sz--) {
        *p++ = x;
    }
    return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;

    while (n--)
        *d++ = *s++;

    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char tmp[n];
    memcpy(tmp, src, n);
    memcpy(dest, tmp, n);
    return dest;
}

int memcmp(const void *str1, const void *str2, size_t count)
{
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;

    while (count-- > 0) {
        if (*s1++ != *s2++) {
            if (s1[-1] < s2[-1]) {
                return -1;
            } else {
                return 1;
            }
        }
    }

    return 0;
}