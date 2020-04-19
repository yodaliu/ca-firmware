#include <sys/io.h>
#include <sys/utils.h>
#include <hal/gpio.h>
#include <hal/auxi.h>

void mini_uart_send(char c)
{
    while (1) {
        if (get32(AUX_MU_LSR_REG) & 0x20)
            break;
    }
    put32(AUX_MU_IO_REG, c);
}

char mini_uart_recv(void)
{
    while (1) {
        if (get32(AUX_MU_LSR_REG) & 0x01)
            break;
    }
    return (get32(AUX_MU_IO_REG) & 0xFF);
}

void mini_uart_send_string(char *str)
{
    uint32_t i;

    for (i = 0; str[i] != '\0'; i ++) {
        mini_uart_send((char)str[i]);
    }
}

void mini_uart_init(void)
{
    set_gpio_mode(14, GPIO_ALT5);
    set_gpio_mode(15, GPIO_ALT5);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(AUX_ENABLES, 1);                  //Enable mini uart (this also enables access to it registers)
    put32(AUX_MU_CNTL_REG, 0);              //Disable auto flow control and disable receiver and transmitter (for now)
    put32(AUX_MU_IER_REG, 0);               //Disable receive and transmit interrupts
    put32(AUX_MU_LCR_REG, 3);               //Enable 8 bit mode
    put32(AUX_MU_MCR_REG, 0);               //Set RTS line to be always high

    uint32_t baudrate_reg = ((SYSTEM_FREQ_CLOCK / BAUD_RATE) >> 3) - 1;
    put32(AUX_MU_BAUD_REG, baudrate_reg);   //Set baund rate to 115200

    put32(AUX_MU_CNTL_REG, 3);              //Finally, enable transmitter and receiver
}