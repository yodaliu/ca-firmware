
#include <sys/exception.h>
#include <sys/utils.h>
#include <sys/isr.h>

void handle_exception(exception_frame *exc)
{

}

void handle_serror(exception_frame *exc)
{

}

void irq_handle(exception_frame *exc)
{
    printf("IRQ Handler\n");

    virtual_timer_isr();

}

void fiq_handle(exception_frame *exc)
{
    printf("FIQ Handler\n");
}

void common_trap_handler(exception_frame *exc)
{
    if ((exc->exc_type & 0xff) == AARCH64_EXC_SYNC_SPX) {
        handle_exception(exc);
    }

    if ((exc->exc_type & 0xff) == AARCH64_EXC_SERR_SPX) {
        handle_exception(exc);
    }

    if ((exc->exc_type & 0xff) == AARCH64_EXC_IRQ_SPX) {
        irq_handle(exc);
    }

    if ((exc->exc_type & 0xff) == AARCH64_EXC_FIQ_SPX) {
        fiq_handle(exc);
    }
}