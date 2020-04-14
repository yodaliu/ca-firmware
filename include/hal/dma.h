#ifndef _DMA_H_
#define _DMA_H_

#include <stdint.h>
#include <hal/address.h>
#include <sys/utils.h>

#define DMA_INT_STATUS  (DMA0_BASE + 0xFE0)

#define DMA_ENABLE_PAGELITE_MSK 0xf
#define DMA_ENABLE_PAGELITE_SH  28
#define DMA_ENABLE_PAGE_MSK     0xf
#define DMA_ENABLE_PAGE_SH      24
#define DMA_ENABLE      (DMA0_BASE + 0xFF0)

struct dma_cb {
#define DMA_TI_NO_WIDE_BURSTS           BIT(26)
#define DMA_TI_WAITS_MSK                0x1f
#define DMA_TI_WAITS_SH                 21
#define DMA_TI_PERMAP_MSK               0x1f
#define DMA_TI_PERMAP_SH                16
#define DMA_TI_BURST_LENGTH_MSK         0xf
#define DMA_TI_BURST_LENGTH_SH          12
#define DMA_TI_SRC_IGNORE               BIT(11)
#define DMA_TI_SRC_DREQ                 BIT(10)
#define DMA_TI_SRC_WIDTH                BIT(9)
#define DMA_TI_SRC_INC                  BIT(8)
#define DMA_TI_DEST_IGNORE              BIT(7)
#define DMA_TI_DEST_DREQ                BIT(6)
#define DMA_TI_DEST_WIDTH               BIT(5)
#define DMA_TI_DEST_INC                 BIT(4)
#define DMA_TI_WAIT_RESP                BIT(3)
#define DMA_TI_TDMODE                   BIT(1)
#define DMA_TI_INTEN                    BIT(0)
    uint32_t TI;
    uint32_t SOURCE_AD;
    uint32_t DEST_AD;
#define DMA_TXFR_YLENGTH_MSK            0x3fff
#define DMA_TXFR_YLENGTH_SH             16
#define DMA_TXFR_XLENGTH_MSK            0xffff
#define DMA_TXFR_XLENGTH_SH             0
    uint32_t TXFR_LEN;
#define DMA_STRIDE_D_STRIDE_MSK         0xffff
#define DMA_STRIDE_D_STRIDE_SH          16
#define DMA_STRIDE_S_STRIDE_MSK         0xffff
#define DMA_STRIDE_S_STRIDE_SH          0
    uint32_t STRIDE;
    uint32_t NEXTCONBK;
};

struct dma_register {
#define DMA_RESET                             BIT(31)
#define DMA_ABORT                             BIT(30)
#define DMA_DISDEBUG                          BIT(29)
#define DMA_WAIT_FOR_OUTSTANDING_WRITES       BIT(28)
#define DMA_PANIC_PRIORITY_MSK                0xf
#define DMA_PANIC_PRIORITY_SH                 20
#define DMA_PRIORITY_MSK                      0xf
#define DMA_PRIORITY_SH                       16
#define DMA_ERROR                             BIT(8)
#define DMA_WAITING_FOR_OUTSTANDING_WRITES    BIT(6)
#define DMA_DREQ_STOPS_DMA                    BIT(5)
#define DMA_PAUSED                            BIT(4)
#define DMA_DREQ                              BIT(3)
#define DMA_INT                               BIT(2)
#define DMA_END                               BIT(1)
#define DMA_ACTIVE                            BIT(0)
    uint32_t CS;
    uint32_t CONBLK_AD;
    struct dma_cb CB;
#define DMA_DEBUG_LITE                        BIT(28)
#define DMA_DEBUG_VERSION_MSK                 0x7
#define DMA_DEBUG_VERSION_SH                  25
#define DMA_DEBUG_DMA_STATE_MSK               0x1Ff
#define DMA_DEBUG_DMA_STATE_SH                16
#define DMA_DEBUG_DMA_ID_MSK                  0xff
#define DMA_DEBUG_DMA_ID_SH                   8
#define DMA_DEBUG_OUTSTANDING_WRITES_MSK      0xf
#define DMA_DEBUG_OUTSTANDING_WRITES_SH       4
#define DMA_DEBUG_READ_ERROR                  BIT(2)
#define DMA_DEBUG_FIFO_ERROR                  BIT(1)
#define DMA_DEBUG_READ_LAST_NOT_SET_ERROR     BIT(0)
    uint32_t DEBUG;
};

struct dma_lite_cb {
#define DMA_LITE_TI_WAITS_MSK                0x1f
#define DMA_LITE_TI_WAITS_SH                 21
#define DMA_LITE_TI_PERMAP_MSK               0x1f
#define DMA_LITE_TI_PERMAP_SH                16
#define DMA_LITE_TI_BURST_LENGTH_MSK         0xf
#define DMA_LITE_TI_BURST_LENGTH_SH          12
#define DMA_LITE_TI_SRC_DREQ                 BIT(10)
#define DMA_LITE_TI_SRC_WIDTH                BIT(9)
#define DMA_LITE_TI_SRC_INC                  BIT(8)
#define DMA_LITE_TI_DEST_DREQ                BIT(6)
#define DMA_LITE_TI_DEST_WIDTH               BIT(5)
#define DMA_LITE_TI_DEST_INC                 BIT(4)
#define DMA_LITE_TI_WAIT_RESP                BIT(3)
#define DMA_LITE_TI_INTEN                    BIT(0)
    uint32_t TI;
    uint32_t SOURCE_AD;
    uint32_t DEST_AD;
#define DMA_LITE_TXFR_XLENGTH_MSK            0xffff
#define DMA_LITE_TXFR_XLENGTH_SH             0
    uint32_t TXFR_LEN;
    uint32_t RSVD;
    uint32_t NEXTCONBK;
};

struct dma_lite_register {
    uint32_t CS;
    uint32_t CONBLK_AD;
    struct dma_lite_cb CB;
#define DMA_LITE_DEBUG_LITE                        BIT(28)
#define DMA_LITE_DEBUG_VERSION_MSK                 0x7
#define DMA_LITE_DEBUG_VERSION_SH                  25
#define DMA_LITE_DEBUG_DMA_STATE_MSK               0x1Ff
#define DMA_LITE_DEBUG_DMA_STATE_SH                16
#define DMA_LITE_DEBUG_DMA_ID_MSK                  0xff
#define DMA_LITE_DEBUG_DMA_ID_SH                   8
#define DMA_LITE_DEBUG_OUTSTANDING_WRITES_MSK      0xf
#define DMA_LITE_DEBUG_OUTSTANDING_WRITES_SH       4
#define DMA_LITE_DEBUG_READ_ERROR                  BIT(2)
#define DMA_LITE_DEBUG_FIFO_ERROR                  BIT(1)
#define DMA_LITE_DEBUG_READ_LAST_NOT_SET_ERROR     BIT(0)
    uint32_t DEBUG;
};

struct dma4_cb {
#define DMA4_TI_WAIT_CYCLES_MSK     0xff
#define DMA4_TI_WAIT_CYCLES_SH      24
#define DMA4_TI_S_WAITS_MSK         0xff
#define DMA4_TI_S_WAITS_SH          16
#define DMA4_TI_D_DREQ              BIT(15)
#define DMA4_TI_S_DREQ              BIT(14)
#define DMA4_TI_PERMAP_MSK          0x1f
#define DMA4_TI_PERMAP_SH           9
#define DMA4_TI_WAIT_RD_RESP        BIT(3)
#define DMA4_TI_WAIT_RESP           BIT(2)
#define DMA4_TI_TDMODE              BIT(1)
#define DMA4_TI_INTEN               BIT(0)
    uint32_t TI;
    uint32_t SRC;
#define DMA4_SRCI_STRIDE_MSK        0xffff
#define DMA4_SRCI_STRIDE_SH         16
#define DMA4_SRCI_IGNORE            BIT(15)
#define DMA4_SRCI_SIZE_MSK          0x3
#define DMA4_SRCI_SIZE_SH           13
#define DMA4_SRCI_INC               BIT(12)
#define DMA4_SRCI_BURST_LENGTH_MSK  0xf
#define DMA4_SRCI_BURST_LENGTH_SH   8
#define DMA4_SRCI_ADDR_MSK          0xff
#define DMA4_SRCI_ADDR_SH           0
    uint32_t SRCI;
    uint32_t DEST;
#define DMA4_DESTI_STRIDE_MSK        0xffff
#define DMA4_DESTI_STRIDE_SH         16
#define DMA4_DESTI_IGNORE            BIT(15)
#define DMA4_DESTI_SIZE_MSK          0x3
#define DMA4_DESTI_SIZE_SH           13
#define DMA4_DESTI_INC               BIT(12)
#define DMA4_DESTI_BURST_LENGTH_MSK  0xf
#define DMA4_DESTI_BURST_LENGTH_SH   8
#define DMA4_DESTI_ADDR_MSK          0xff
#define DMA4_DESTI_ADDR_SH           0
    uint32_t DESTI;
#define DMA4_LEN_YLENGTH_MSK            0x3fff
#define DMA4_LEN_YLENGTH_SH             16
#define DMA4_LEN_XLENGTH_MSK            0xffff
#define DMA4_LEN_XLENGTH_SH             0
    uint32_t LEN;
    uint32_t NEXT_CB;
};

struct dma4_register {
#define DMA4_HALT                           BIT(31)
#define DMA4_ABORT                          BIT(30)
#define DMA4_DISDEBUG                       BIT(29)
#define DMA4_WAIT_FOR_OUTSTANDING_WRITES    BIT(28)
#define DMA4_OUTSTANDING_TRANSACTIONS       BIT(25)
#define DMA4_DMA_BUSY                       BIT(24)
#define DMA4_PANIC_QOS_MSK                  0xf
#define DMA4_PANIC_QOS_SH                   20
#define DMA4_QOS_MSK                        0xf
#define DMA4_QOS_SH                         16
#define DMA4_ERROR                          BIT(10)
#define DMA4_WAITING_FOR_OUTSTANDING_WRITES BIT(7)
#define DMA4_DREQ_STOPS_DMA                 BIT(6)
#define DMA4_WR_PAUSED                      BIT(5)
#define DMA4_RD_PAUSED                      BIT(4)
#define DMA4_DREQ                           BIT(3)
#define DMA4_INT                            BIT(2)
#define DMA4_END                            BIT(1)
#define DMA4_ACTIVE                         BIT(0)
    uint32_t CS;
    uint32_t CB_AD;
#define DMA4_DEBUG_VERSION_MSK              0xf
#define DMA4_DEBUG_VERSION_SH               28
#define DMA4_DEBUG_ID_MSK                   0xf
#define DMA4_DEBUG_ID_SH                    24
#define DMA4_RESET                          BIT(23)
#define DMA4_W_STATE_MSK                    0xf
#define DMA4_W_STATE_SH                     18
#define DMA4_R_STATE_MSK                    0xf
#define DMA4_R_STATE_SH                     14
#define DMA4_DISABLE_CLK_GATE               BIT(11)
#define DMA4_ABORT_ON_ERROR                 BIT(10)
#define DMA4_HALT_ON_ERROR                  BIT(9)
#define DMA4_INT_ON_ERROR                   BIT(8)
#define DMA4_READ_CB_ERROR                  BIT(3)
#define DMA4_READ_ERROR                     BIT(2)
#define DMA4_FIFO_ERROR                     BIT(1)
#define DMA4_WRITE_ERROR                    BIT(0)
    uint32_t DEBUG;
    struct dma4_cb CB;
#define DMA4_DEBUG2_OUTSTANDING_READS_MSK  0xff
#define DMA4_DEBUG2_OUTSTANDING_READS_SH   16
#define DMA4_DEBUG2_OUTSTANDING_WRITES_MSK 0xff
#define DMA4_DEBUG2_OUTSTANDING_WRITES_SH  0
    uint32_t DEBUG2;
};

enum dma4_write_status {
    W_IDLE = 0,
    W_PRELOAD = 1,
    W_CALC = 2,
    W_WRITE4K = 3,
    W_READFIFO_EMPTY = 4,
    W_WAIT_OUTSTANDING = 5
};

enum dma4_read_status {
    R_IDLE = 0,
    R_WAIT_CB_DATA = 1,
    R_CALC = 2,
    R_READ4K = 3,
    R_READING = 4,
    R_READFIFO_FULL = 5,
    R_WAIT_WRITE_COMPLETE = 6
};

#endif //#ifndef _DMA_H_