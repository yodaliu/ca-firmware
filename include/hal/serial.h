#ifndef _SERIAL_H_
#define _SERIAL_H_


#include <stdint.h>
#include <hal/address.h>
#include <sys/utils.h>

struct serial_register {
#define SERIAL_C_I2CEN      BIT(15)
#define SERIAL_C_INTR       BIT(10)
#define SERIAL_C_INTT       BIT(9)
#define SERIAL_C_INTD       BIT(8)
#define SERIAL_C_ST         BIT(7)
#define SERIAL_C_CLEAR_MSK  (BIT(5)|BIT(4))
#define SERIAL_C_CLEAR_SH   4
#define SERIAL_C_READ       BIT(0)
    uint32_t C;
#define SERIAL_S_CLKT       BIT(9)
#define SERIAL_S_ERR        BIT(8)
#define SERIAL_S_RXF        BIT(7)
#define SERIAL_S_TXE        BIT(6)
#define SERIAL_S_RXD        BIT(5)
#define SERIAL_S_TXD        BIT(4)
#define SERIAL_S_RXR        BIT(3)
#define SERIAL_S_TXW        BIT(2)
#define SERIAL_S_DONE       BIT(1)
#define SERIAL_S_TA         BIT(0)
    uint32_t S;
#define SERIAL_DLEN_MSK     0xffff
#define SERIAL_DLEN_SH      0
    uint32_t DLEN;
#define SERIAL_A_ADDR_MSK   0x3f
#define SERIAL_A_ADDR_SH    0
    uint32_t A;
#define SERIAL_FIFO_DATA_MSK 0xff
#define SERIAL_FIFO_DATA_SH  0
    uint32_t FIFO;
#define SERIAL_DIV_CDIV_MSK 0xffff
#define SERIAL_DIV_CDIV_SH  0
    uint32_t DIV;
#define SERIAL_DEL_FEDL_MSK 0xffff
#define SERIAL_DEL_FEDL_SH  15
#define SERIAL_DEL_REDL_MSK 0xffff
#define SERIAL_DEL_REDL_SH  0
    uint32_t DEL;
#define SERIAL_CLKT_TOUT_MSK 0xffff
#define SERIAL_CLKT_TOUT_SH  0
    uint32_t CLKT;
};

#endif //#ifndef _SERIAL_H_