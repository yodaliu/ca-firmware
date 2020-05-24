#include <stdint.h>
#include <sys/io.h>
#include <sys/utils.h>
#include <hal/mbox.h>
#include <hal/gpio.h>
#include <hal/uart.h>

void uart_init()
{
    put32(UART0_CR, 0);         // turn off UART0

    /* set up clock for consistent divisor values */
    mbox[0] = 9 * 4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;           // UART clock
    mbox[6] = 4000000;     // 4MHz
    mbox[7] = 0;           // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    mbox_call(MBOX_CH_PROP);

    set_gpio_mode(14, GPIO_ALT0);
    set_gpio_mode(15, GPIO_ALT0);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(UART0_ICR, 0x7FF);        // clear interrupts
    put32(UART0_IBRD, 2);           // 115200 baud
    put32(UART0_FBRD, 0xB);
    put32(UART0_LCRH, (0b11 << 5) | BIT(4)); // 8n1
    put32(UART0_CR, 0x301);         // enable Tx, Rx, FIFO

    while (!(get32(UART0_FR) & BIT(4))) {
        get32(UART0_DR);
    }
}

void uart_send(char c)
{
    /* wait until we can send */
    do {
        asm volatile("nop");
    } while (get32(UART0_FR) & 0x20);

    /* write the character to the buffer */
    put32(UART0_DR, c);
}

char uart_getc()
{
    char ch;

    /* wait until something is in the buffer */
    do {
        asm volatile("nop");
    } while (get32(UART0_FR) & 0x10);

    /* read it and return */
    ch = (char)(get32(UART0_DR));

    /* convert carrige return to newline */
    return ch;
}

void uart_send_string(char *str)
{
    uint32_t i;

    for (i = 0; str[i] != '\0'; i ++) {
        uart_send((char)str[i]);
    }
}