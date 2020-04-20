#include <stdint.h>
#include <sys/io.h>
#include <sys/utils.h>
#include <hal/mbox.h>

volatile uint32_t  __attribute__((aligned(16))) mbox[36];

/* Make a mailbox call. Returns 0 on failure, non-zero on success */
int mbox_call(unsigned char ch)
{
    unsigned int r = (((unsigned int)((unsigned long)&mbox) & ~0xF) | (ch & 0xF));

    /* wait until we can write to the mailbox */
    do {
        asm volatile("nop");
    } while (get32(VC_MBOX_STATUS) & MBOX_FULL);

    /* write the address of our message to the mailbox with channel identifier */
    put32(VC_MBOX_WRITE, r);

    /* now wait for the response */
    while (1) {
        /* is there a response? */
        do {
            asm volatile("nop");
        } while (get32(VC_MBOX_STATUS) & MBOX_EMPTY);

        /* is it a response to our message? */
        if (r == get32(VC_MBOX_READ))
            /* is it a valid successful response? */
            return mbox[1] == MBOX_RESPONSE;
    }

    return 0;
}