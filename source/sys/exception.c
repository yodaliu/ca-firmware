
#include <sys/exception.h>
#include <sys/isr.h>
#include <sys/io.h>
#include <hal/gicv2.h>

void handle_exception(exception_frame *exc)
{

}

void handle_serror(exception_frame *exc)
{

}

void irq_handle(exception_frame *exc)
{
    uint16_t id;

    printf("IRQ Handler\n");

    id = get32(GICC_IAR) & 0x3FF;
    printf("INT ID: %x\n", id);

    clear_intrpt_pending(id);
    if (id == GIC_ARM_IRQ_V_TIMER)
        virtual_timer_isr();

    put32(GICC_EOIR, id);

}

void fiq_handle(exception_frame *exc)
{
    uint16_t id;

    printf("FIQ Handler\n");

    id = get32(GICC_IAR) & 0x3FF;
    printf("INT ID: %x\n", id);

    clear_intrpt_pending(id);
    if (id == GIC_ARM_IRQ_V_TIMER)
        virtual_timer_isr();

    put32(GICC_EOIR, id);

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