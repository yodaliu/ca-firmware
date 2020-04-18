#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include "address.h"

struct spi_register {
#define SPI_CS_LENG_LONG BIT(25)
#define SPI_CS_DMA_LEN BIT(24)
#define SPI_CS_CSPOL2 BIT(23)
#define SPI_CS_CSPOL1 BIT(22)
#define SPI_CS_CSPOL0 BIT(21)
#define SPI_CS_RXF BIT(20)
#define SPI_CS_RXR BIT(19)
#define SPI_CS_TXD BIT(18)
#define SPI_CS_RXD BIT(17)
#define SPI_CS_DONE BIT(16)
#define SPI_CS_TE_EN BIT(15)
#define SPI_CS_LMONO BIT(14)
#define SPI_CS_LEN BIT(13)
#define SPI_CS_REN BIT(12)
#define SPI_CS_ADCS BIT(11)
#define SPI_CS_INTR BIT(10)
#define SPI_CS_INTD BIT(9)
#define SPI_CS_DMAEN BIT(8)
#define SPI_CS_TA BIT(7)
#define SPI_CS_CSPOL BIT(6)
#define SPI_CS_CLEAR_MSK 0x3
#define SPI_CS_CLEAR_SH 4
#define SPI_CS_CPOL BIT(3)
#define SPI_CS_CPHA BIT(2)
#define SPI_CS_CS_MSK 0x3
#define SPI_CS_CS_SH 0
    uint32_t CS;
    uint32_t FIFO;
#define SPI_CLK_CDIV_MSK 0xffff
#define SPI_CLK_CDIV_SH 0
    uint32_t CLK;
#define SPI_DLEN_LEN_MSK 0xffff
#define SPI_DLEN_LEN_SH 0
    uint32_t DLEN;
#define SPI_LTOH_TOH_MSK 0xf
#define SPI_LTOH_TOH_SH 0
    uint32_t LTOH;
#define SPI_DC_RPANIC_MSK 0xff
#define SPI_DC_RPANIC_SH 24
#define SPI_DC_RDREQ_MSK 0xff
#define SPI_DC_RDREQ_SH 16
#define SPI_DC_TPANIC_MSK 0xff
#define SPI_DC_TPANIC_SH 8
#define SPI_DC_TDREQ_MSK 0xff
#define SPI_DC_TDREQ_SH 0
    uint32_t DC;
};

#endif //#ifndef _SPI_H_
