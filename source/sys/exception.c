
#include <sys/exception.h>
#include <sys/utils.h>

void handle_exception(exception_frame *exc)
{
    printf("An exception occur\n");
}

void irq_handle(exception_frame *exc)
{
    printf("IRQ Handler\n");
}

void common_trap_handler(exception_frame *exc)
{
    if ((exc->exc_type & 0xff) == AARCH64_EXC_SYNC_SPX) {
        printf("AARCH64_EXC_SYNC_SPX\n");
        handle_exception(exc);
    }

    if ((exc->exc_type & 0xff) == AARCH64_EXC_IRQ_SPX) {
        printf("AARCH64_EXC_IRQ_SPX\n");
        irq_handle(exc);
    }
}