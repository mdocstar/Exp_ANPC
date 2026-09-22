#ifndef	_W5300_H_
#define	_W5300_H_

#include "types.h"
/**
 * SOCKET count of W5300 
 */
#define	MAX_SOCK_NUM		8


#define __DEF_IINCHIP_DIRECT_MODE__     1    /**< Direct address mode */
#define __DEF_IINCHIP_INDIRECT_MODE__   2    /**< Indirect address mode */

/**
 * It is used to decide to W5300 host interface mode. 
 */
#define __DEF_IINCHIP_ADDRESS_MODE__           __DEF_IINCHIP_DIRECT_MODE__
//#define __DEF_IINCHIP_ADDRESS_MODE__         __DEF_IINCHIP_INDIRECT_MODE__

/**
 * Define the base address of W5300 on your target host system.
 */
#define __DEF_IINCHIP_MAP_BASE__ 0x4000

#if (__DEF_IINCHIP_ADDRESS_MODE__ == __DEF_IINCHIP_DIRECT_MODE__)
   #define COMMON_REG_BASE   __DEF_IINCHIP_MAP_BASE__          /**< The base address of COMMON_REG */
   #define SOCKET_REG_BASE   __DEF_IINCHIP_MAP_BASE__ + 0x0200 /**< The base address of SOCKET_REG */   
#else
   #define COMMON_REG_BASE     0                               
   #define SOCKET_REG_BASE     0x0200                          
#endif

#define SOCKET_REG_SIZE    0x40     // SOCKET Regsiter Count per Channel




#define __DEF_C__                  0   /**< Using C code */
#define __DEF_MCU_DEP_INLINE_ASM__ 1   /**< Using inline ASM code */
#define __DEF_MCU_DEP_DMA__        2   /**< Using DMA controller */



/**
 * It define how to access to the intenal TX/RX memory of W5300.
 */
#define __DEF_IINCHIP_BUF_OP__      __DEF_C__
//#define __DEF_IINCHIP_BUF_OP__    __DEF_MCU_DEP_INLINE_ASM__
//#define __DEF_IINCHIP_BUF_OP__    __DEF_MCU_DEP_DMA__


/**
 * Enter a critical section
 */
#define IINCHIP_CRITICAL_SECTION_ENTER() {}

/**
 * Exit a critical section
 */
#define IINCHIP_CRITICAL_SECTION_EXIT() {}

 
/** 
 *  Mode register. 
 */
#define MR              (__DEF_IINCHIP_MAP_BASE__)
#define MR0             MR
#define MR1             (MR + 1)

/**
  *  Indirect mode address register.
 */ 
#define IDM_AR          (__DEF_IINCHIP_MAP_BASE__ + 0x02)
#define IDM_AR0         IDM_AR
#define IDM_AR1         (IDM_AR + 1)

/**
  *  Indirect mode data register.
 */ 
#define IDM_DR          (__DEF_IINCHIP_MAP_BASE__ + 0x04)
#define IDM_DR0         (__DEF_IINCHIP_MAP_BASE__ + 0x04)
#define IDM_DR1         (IDM_DR + 1)

/**
 *  Interrupt register
 */
#define IR              (COMMON_REG_BASE + 0x02)
#define IR0             IR
#define IR1             (IR + 1);

/**
 *  Interrupt mask register
 */
#define IMR             (COMMON_REG_BASE + 0x04)
#define IMR0            IMR
#define IMR1            (IMR + 1)


//#define ICFGR           (COMMON_REG_BASE + 0x06)
//#define ICFGR0          ICFGR
//#define ICFGR1          (ICFGR0 + 1)

/**
 *  Source hardware address register
 */
#define SHAR            (COMMON_REG_BASE + 0x08)
#define SHAR0           SHAR
#define SHAR1           (SHAR + 1)
#define SHAR2           (SHAR + 2)
#define SHAR3           (SHAR + 3)
#define SHAR4           (SHAR + 4)
#define SHAR5           (SHAR + 5)


/**
 *  Gateway IP address register
 */
#define GAR             (COMMON_REG_BASE + 0x10)
#define GAR0            GAR
#define GAR1            (GAR + 1)
#define GAR2            (GAR + 2)
#define GAR3            (GAR + 3)

/**
 *  Subnet mask register
 */
#define SUBR            (COMMON_REG_BASE + 0x14)
#define SUBR0           SUBR
#define SUBR1           (SUBR + 1)
#define SUBR2           (SUBR + 2)
#define SUBR3           (SUBR + 3)

/**
 *  Source IP address register
 */
#define SIPR            (COMMON_REG_BASE + 0x18)
#define SIPR0           SIPR
#define SIPR1           (SIPR + 1)
#define SIPR2           (SIPR + 2)
#define SIPR3           (SIPR + 3)

/**
 *  Retransmittion timeout-period register 
 */
#define RTR             (COMMON_REG_BASE + 0x1C)
#define RTR0            RTR
#define RTR1            (RTR + 1)

/**
 *  Retransmittion retry count reigster
 */
#define RCR             (COMMON_REG_BASE + 0x1E)
#define RCR0            RCR
#define RCR1            (RCR + 1)

/**
 *  Transmit memory size of each SOCKET reigster
 */
#define TMS01R          (COMMON_REG_BASE + 0x20)
#define TMS23R          (TMS01R + 2) /**< Refer to TMS01R. */
#define TMS45R          (TMS01R + 4) /**< Refer to TMS01R. */
#define TMS67R          (TMS01R + 6) /**< Refer to TMS01R. */

#define TMSR0           TMS01R
#define TMSR1           (TMSR0 + 1)
#define TMSR2           (TMSR0 + 2)
#define TMSR3           (TMSR0 + 3)
#define TMSR4           (TMSR0 + 4)
#define TMSR5           (TMSR0 + 5)
#define TMSR6           (TMSR0 + 6)
#define TMSR7           (TMSR0 + 7)


/**
 *  Transmit memory size of each SOCKET reigster
 */
#define RMS01R          (COMMON_REG_BASE + 0x28)
#define RMS23R          (RMS01R + 2)   /**< Refer to RMS01R. */
#define RMS45R          (RMS01R + 4)   /**< Refer to RMS01R. */
#define RMS67R          (RMS01R + 6)   /**< Refer to RMS01R. */

#define RMSR0           RMS01R
#define RMSR1           (RMSR0 + 1)
#define RMSR2           (RMSR0 + 2)
#define RMSR3           (RMSR0 + 3)
#define RMSR4           (RMSR0 + 4)
#define RMSR5           (RMSR0 + 5)
#define RMSR6           (RMSR0 + 6)
#define RMSR7           (RMSR0 + 7)



/**
 *  Memory type register
 */
#define MTYPER          (COMMON_REG_BASE + 0x30)
#define MTYPER0         MTYPER
#define MTYPER1         (MTYPER + 1)

/**
 *  Authentication type register
 */
#define PATR            (COMMON_REG_BASE + 0x32)
#define PATR0           PATR
#define PATR1           (PATR + 1)

//#define PPPALGOR      (COMMON_REG_BASE + 0x34)
//#define PPPALGOR0     PPPALGOR
//#define PPPALGOR1     (PPPALGOR + 1)

/**
 *  PPP link control protocol request timer register
 */
#define PTIMER          (COMMON_REG_BASE + 0x36)
#define PTIMER0         PTIMER
#define PTIMER1         (PTIMER + 1)

/**
 *  PPP LCP magic number register
 */
#define PMAGICR         (COMMON_REG_BASE + 0x38)
#define PMAGICR0        PMAGICR
#define PMAGICR1        (PMAGICR + 1)


/**
 *  PPPoE session ID register
 */
#define PSIDR           (COMMON_REG_BASE + 0x3C)
#define PSIDR0          PSIDR
#define PSIDR1          (PSIDR + 1)

/**
 *  PPPoE destination hardware address register
 */
#define PDHAR           (COMMON_REG_BASE + 0x40)
#define PDHAR0          PDHAR
#define PDHAR1          (PDHAR + 1)
#define PDHAR2          (PDHAR + 2)
#define PDHAR3          (PDHAR + 3)
#define PDHAR4          (PDHAR + 4)
#define PDHAR5          (PDHAR + 5)

/**
 *  Unreachable IP address register 
 *
 * RESET : 0.0.0.0 \n 
 * When trying to transmit UDP data to destination port number which is not open, 
 * W5300 can receive ICMP (Destination port unreachable) packet. \n
 * In this case, IR(IR_DPUR) becomes '1'. 
 * And destination IP address and unreachable port number of ICMP packet
 * can be acquired through UIPR and UPORTR.
 */
#define UIPR            (COMMON_REG_BASE + 0x48)
#define UIPR0           UIPR
#define UIPR1           (UIPR + 1)
#define UIPR2           (UIPR + 2)
#define UIPR3           (UIPR + 3)

/**
 *  Unreachable port number register
 */
#define UPORTR          (COMMON_REG_BASE + 0x4C)
#define UPORTR0         UPORTR
#define UPORTR1         (UPORT + 1)

/**
 *  Fragment MTU register
 */
#define FMTUR           (COMMON_REG_BASE + 0x4E)
#define FMTUR0          FMTUR
#define FMTUR1          (FMTUR + 1)

//#define Sn_RTCR(n)      (COMMON_REG_BASE + 0x50 + n*2)
//#define Sn_RTCR0(n)     Sn_RTCR(n)
//#define Sn_RTCR1(n)     (Sn_RTCR(n)+1)

/**
 *  PIN 'BRDYn' configure register
 */
#define Pn_BRDYR(n)     (COMMON_REG_BASE + 0x60 + n*4)
#define Pn_BRDYR0(n)    Pn_BRDYR(n)
#define Pn_BRDYR1(n)    (Pn_BRDYR(n) + 1)

/**
 *  PIN 'BRDYn' buffer depth Register
 */
#define Pn_BDPTHR(n)    (COMMON_REG_BASE + 0x60 + n*4 + 2)
#define Pn_BDPTHR0(n)   Pn_BDPTHR(n)
#define Pn_BDPTHR1(n)   (Pn_BDPTHR(n) + 1)

/**
 *  W5300 identification register
 */
#define IDR             (COMMON_REG_BASE + 0xFE)
#define IDR1            (IDR + 1)


/**
 *  SOCKETn mode register
 */
#define Sn_MR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x00)
#define Sn_MR0(n)       Sn_MR(n)
#define Sn_MR1(n)       (Sn_MR(n)+1)

/**
 *  SOCKETn command register
 */                        
#define Sn_CR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x02)
#define Sn_CR0(n)       Sn_CR(n)
#define Sn_CR1(n)       (Sn_CR(n) + 1)   

/**
 *  SOCKETn interrupt mask register
 */
#define Sn_IMR(n)       (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x04)
#define Sn_IMR0(n)      Sn_IMR(n)
#define Sn_IMR1(n)      (Sn_IMR(n)+1)

/**
 *  SOCKETn interrupt register
 */
#define Sn_IR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x06)
#define Sn_IR0(n)       Sn_IR(n)
#define Sn_IR1(n)       (Sn_IR(n)+1)

/**
 *  SOCKETn status register
 */
#define Sn_SSR(n)       (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x08)
#define Sn_SSR0(n)      Sn_SSR(n)
#define Sn_SSR1(n)      (Sn_SSR(n)+1)

/**
 *  SOCKETn source port register
 */
#define Sn_PORTR(n)     (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0A)
#define Sn_PORTR0(n)    Sn_PORTR(n)
#define Sn_PORTR1(n)    (Sn_PORTR(n)+1)

/**
 *  SOCKETn destination hardware address register
 */
#define Sn_DHAR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0C)
#define Sn_DHAR0(n)     Sn_DHAR(n)
#define Sn_DHAR1(n)     (Sn_DHAR(n)+1)
#define Sn_DHAR2(n)     (Sn_DHAR(n)+2)
#define Sn_DHAR3(n)     (Sn_DHAR(n)+3)
#define Sn_DHAR4(n)     (Sn_DHAR(n)+4)
#define Sn_DHAR5(n)     (Sn_DHAR(n)+5)

/**
 *  SOCKETn destination port register
 */
#define Sn_DPORTR(n)    (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x12)
#define Sn_DPORTR0(n)   Sn_DPORTR(n)
#define Sn_DPORTR1(n)   (Sn_DPORTR(n)+1)


/**
 *  SOCKETn destination IP address register
 */
#define Sn_DIPR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x14)
#define Sn_DIPR0(n)     Sn_DIPR(n)
#define Sn_DIPR1(n)     (Sn_DIPR(n)+1)
#define Sn_DIPR2(n)     (Sn_DIPR(n)+2)
#define Sn_DIPR3(n)     (Sn_DIPR(cnnh)+3)

/**
 *  SOCKETn maximum segment size register
 */
#define Sn_MSSR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x18)
#define Sn_MSSR0(n)     Sn_MSSR(n)
#define Sn_MSSR1(n)     (Sn_MSSR(n)+1)

/**
 *  SOCKETn protocol of IP header field register
 */
#define Sn_PROTOR(n)		(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1A)
/**
 *  SOCKETn keep alive timer register
 */
#define Sn_KPALVTR(n)   Sn_PROTOR(n)
#define Sn_PROTOR1(n)   (Sn_PROTOR(n)+1)

/**
 *  SOCKETn IP type of service(TOS) register
 */
#define Sn_TOSR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1C)
#define Sn_TOSR0(n)     Sn_TOSR(n)
#define Sn_TOSR1(n)     (Sn_TOSR(n)+1)

/**
 *  SOCKETn IP time to live(TTL) register
 */
#define Sn_TTLR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1E)
#define Sn_TTLR0(n)     Sn_TTLR(n)
#define Sn_TTLR1(n)     (Sn_TTLR(n)+1)

/**
 *  SOCKETn TX write size register
 */
#define Sn_TX_WRSR(n)		(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x20)
#define Sn_TX_WRSR0(n)		Sn_TX_WRSR(n)
#define Sn_TX_WRSR1(n)		(Sn_TX_WRSR(n) + 1)
#define Sn_TX_WRSR2(n)		(Sn_TX_WRSR(n) + 2)
#define Sn_TX_WRSR3(n)		(Sn_TX_WRSR(n) + 3)

/**
 *  SOCKETn TX free size register
 */
#define Sn_TX_FSR(n)       (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0024)
#define Sn_TX_FSR0(n)      Sn_TX_FSR(n)
#define Sn_TX_FSR1(n)      (Sn_TX_FSR(n) + 1)
#define Sn_TX_FSR2(n)      (Sn_TX_FSR(n) + 2)
#define Sn_TX_FSR3(n)      (Sn_TX_FSR(n) + 3)

/**
 *  SOCKETn RX received size register
 */
#define Sn_RX_RSR(n)       (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0028)
#define Sn_RX_RSR0(n)      Sn_RX_RSR(n)
#define Sn_RX_RSR1(n)      (Sn_RX_RSR(n) + 1)
#define Sn_RX_RSR2(n)      (Sn_RX_RSR(n) + 2)
#define Sn_RX_RSR3(n)      (Sn_RX_RSR(n) + 3)

/**
 *  SOCKETn fragment register
 */
#define Sn_FRAGR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x002C)
#define Sn_FRAGR0(n)       Sn_FRAGR(n)
#define Sn_FRAGR1(n)       (Sn_FRAGR(n) + 1)

/**
 *  SOCKETn TX FIFO register
 */
#define Sn_TX_FIFOR(n)     (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2E)
#define Sn_TX_FIFOR0(n)    Sn_TX_FIFO(n)
#define Sn_TX_FIFOR1(n)    (Sn_TX_FIFO(n) + 1)

/**
 *  SOCKET n RX FIFO register
 */
#define Sn_RX_FIFOR(n)     (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x30)
#define Sn_RX_FIFOR0(n)    Sn_RX_FIFO(n)
#define Sn_RX_FIFOR1(n)    (Sn_RX_FIFO(n) + 1)


//#define Sn_TX_SADR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x32)
//#define Sn_TX_SADR0(n)     Sn_TX_SADR(n)
//#define Sn_TX_SADR1(n)     (Sn_TX_SADR(n) + 1)

//#define Sn_RX_SADR(n)      (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x34)
//#define Sn_RX_SADR0(n)     Sn_RX_SADR(n)
//#define Sn_RX_SADR1(n)     (Sn_RX_SADR(n) + 1)

//#define Sn_TX_RD(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x36)
//#define Sn_TX_RD0(n)       (Sn_TX_RD(n) + 1)
//#define Sn_TX_RD1(n)       (Sn_TX_RD(n) + 1)

//#define Sn_TX_WR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x38)
//#define Sn_TX_WR0(n)       Sn_TX_WR(n)
//#define Sn_TX_WR1(n)       (Sn_TX_WR(n) + 1)

//#define Sn_TX_ACK(n)       (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3A)
//#define Sn_TX_ACK0(n)      (Sn_TX_ACK(n) + 1)
//#define Sn_TX_ACK1(n)      (Sn_TX_ACK(n) + 1)

//#define Sn_RX_RD(n)       	(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3C)
//#define Sn_RX_RD0(n)	      Sn_RX_RD(n)
//#define Sn_RX_RD1(n)	      (Sn_RX_RD(n) + 1)

//#define Sn_RX_WR(n)        (SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3E)
//#define Sn_RX_WR0(n)        Sn_RX_WR(n)
//#define Sn_RX_WR1(n)       (Sn_RX_WR(n) + 1)



/************************************/
/* The bit of MR regsiter defintion */
/************************************/
#define MR_DBW             (1 << 15)            /**< Data bus width bit of MR. */
#define MR_MPF             (1 << 14)            /**< Mac layer pause frame bit of MR. */
#define MR_WDF(X)          ((X & 0x07) << 11)   /**< Write data fetch time bit of  MR. */
#define MR_RDH             (1 << 10)            /**< Read data hold time bit of MR. */
#define MR_FS              (1 << 8)             /**< FIFO swap bit of MR. */
#define MR_RST             (1 << 7)             /**< S/W reset bit of MR. */
#define MR_MT              (1 << 5)             /**< Memory test bit of MR. */
#define MR_PB              (1 << 4)             /**< Ping block bit of MR. */
#define MR_PPPoE           (1 << 3)             /**< PPPoE bit of MR. */
#define MR_DBS             (1 << 2)             /**< Data bus swap of MR. */
#define MR_IND             (1 << 0)             /**< Indirect mode bit of MR. */


/************************************/ 
/* The bit of IR regsiter defintion */ 
/************************************/ 
#define IR_IPCF            (1 << 7)             /**< IP conflict bit of IR. */
#define IR_DPUR            (1 << 6)             /**< Destination port unreachable bit of IR. */
#define IR_PPPT            (1 << 5)             /**< PPPoE terminate bit of IR. */
#define IR_FMTU            (1 << 4)             /**< Fragment MTU bit of IR. */
#define IR_SnINT(n)        (0x01 << n)          /**< SOCKETn interrupt occurrence bit of IR. */

/*****************************************/ 
/* The bit of Pn_BRDYR regsiter defintion*/ 
/*****************************************/ 
#define Pn_PEN             (1 << 7)             /**< PIN 'BRDYn' enable bit of Pn_BRDYR. */
#define Pn_MT              (1 << 6)             /**< PIN memory type bit of Pn_BRDYR. */
#define Pn_PPL             (1 << 5)             /**< PIN Polarity bit of Pn_BRDYR. */
#define Pn_SN(n)           ((n & 0x07) << 0)    /**< PIN Polarity bit of Pn_BRDYR. */


/***************************************/ 
/* The bit of Sn_MR regsiter defintion */ 
/***************************************/ 
#define Sn_MR_ALIGN        (1 << 8)             /**< Alignment bit of Sn_MR. */
#define Sn_MR_MULTI        (1 << 7)             /**< Multicasting bit of Sn_MR. */
#define Sn_MR_MF           (1 << 6)             /**< MAC filter bit of Sn_MR. */
#define Sn_MR_IGMPv        (1 << 5)             /**< IGMP version bit of Sn_MR. */
#define Sn_MR_ND           (1 << 5)             /**< No delayed ack bit of Sn_MR. */
#define Sn_MR_CLOSE        0x00                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_TCP          0x01                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_UDP          0x02                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_IPRAW        0x03                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_MACRAW       0x04                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_PPPoE        0x05                 /**< Protocol bits of Sn_MR. */


/******************************/ 
/* The values of CR defintion */ 
/******************************/
#define Sn_CR_OPEN         0x01                 /**< OPEN command value of Sn_CR. */
#define Sn_CR_LISTEN       0x02                 /**< LISTEN command value of Sn_CR. */
#define Sn_CR_CONNECT      0x04                 /**< CONNECT command value of Sn_CR. */
#define Sn_CR_DISCON       0x08                 /**< DISCONNECT command value of Sn_CR. */
#define Sn_CR_CLOSE        0x10                 /**< CLOSE command value of Sn_CR. */
#define Sn_CR_SEND         0x20                 /**< SEND command value of Sn_CR. */
#define Sn_CR_SEND_MAC     0x21                 /**< SEND_MAC command value of Sn_CR. */ 
#define Sn_CR_SEND_KEEP    0x22                 /**< SEND_KEEP command value of Sn_CR */
#define Sn_CR_RECV         0x40                 /**< RECV command value of Sn_CR */
#define Sn_CR_PCON         0x23                 /**< PCON command value of Sn_CR */
#define Sn_CR_PDISCON      0x24                 /**< PDISCON command value of Sn_CR */ 
#define Sn_CR_PCR          0x25                 /**< PCR command value of Sn_CR */
#define Sn_CR_PCN          0x26                 /**< PCN command value of Sn_CR */
#define Sn_CR_PCJ          0x27                 /**< PCJ command value of Sn_CR */


/*********************************/ 
/* The values of Sn_IR defintion */ 
/*********************************/
#define Sn_IR_PRECV        0x80                 /**< PPP receive bit of Sn_IR */
#define Sn_IR_PFAIL        0x40                 /**< PPP fail bit of Sn_IR */
#define Sn_IR_PNEXT        0x20                 /**< PPP next phase bit of Sn_IR */
#define Sn_IR_SENDOK       0x10                 /**< Send OK bit of Sn_IR */
#define Sn_IR_TIMEOUT      0x08                 /**< Timout bit of Sn_IR */
#define Sn_IR_RECV         0x04                 /**< Receive bit of Sn_IR */
#define Sn_IR_DISCON       0x02                 /**< Disconnect bit of Sn_IR */
#define Sn_IR_CON          0x01                 /**< Connect bit of Sn_IR */

/**********************************/ 
/* The values of Sn_SSR defintion */ 
/**********************************/
#define SOCK_CLOSED        0x00                 /**< SOCKETn is released */
#define SOCK_ARP           0x01                 /**< ARP-request is transmitted in order to acquire destination hardware address. */
#define SOCK_INIT          0x13                 /**< SOCKETn is open as TCP mode. */
#define SOCK_LISTEN        0x14                 /**< SOCKETn operates as "TCP SERVER" and waits for connection-request (SYN packet) from "TCP CLIENT". */
#define SOCK_SYNSENT       0x15                 /**< Connect-request(SYN packet) is transmitted to "TCP SERVER". */
#define SOCK_SYNRECV       0x16                 /**< Connect-request(SYN packet) is received from "TCP CLIENT". */
#define SOCK_ESTABLISHED   0x17                 /**< TCP connection is established. */
#define SOCK_FIN_WAIT      0x18                 /**< SOCKETn is closing. */
#define SOCK_CLOSING       0x1A                 /**< SOCKETn is closing. */
#define SOCK_TIME_WAIT     0x1B                 /**< SOCKETn is closing. */
#define SOCK_CLOSE_WAIT    0x1C                 /**< Disconnect-request(FIN packet) is received from the peer. */
#define SOCK_LAST_ACK      0x1D                 /**< SOCKETn is closing. */
#define SOCK_UDP           0x22                 /**< SOCKETn is open as UDP mode. */
#define SOCK_IPRAW         0x32                 /**< SOCKETn is open as IPRAW mode. */
#define SOCK_MACRAW        0x42                 /**< SOCKET0 is open as MACRAW mode. */
#define SOCK_PPPoE         0x5F                 /**< SOCKET0 is open as PPPoE mode. */

/* IP PROTOCOL */
#define IPPROTO_IP         0   /* Dummy for IP */
#define IPPROTO_ICMP       1   /* Control message protocol */
#define IPPROTO_IGMP       2   /* Internet group management protocol */
#define IPPROTO_GGP        3   /* Gateway^2 (deprecated) */
#define IPPROTO_TCP        6   /* TCP */
#define IPPROTO_PUP        12  /* PUP */
#define IPPROTO_UDP        17  /* UDP */
#define IPPROTO_IDP        22  /* XNS idp */
#define IPPROTO_ND         77  /* UNOFFICIAL net disk protocol */
#define IPPROTO_RAW        255 /* Raw IP packet */

/***********************
 * Basic I/O  Function *
 ***********************/
/**
 * It reads a value from a register
 */
uint16   IINCHIP_READ(uint32 addr);

/**
 * It writes a value to a register
 */
void     IINCHIP_WRITE(uint32 addr,uint16 data);

/** 
 * It gets MR value.
 */
uint16   getMR(void);

/**
 * It sets MR value
 */
void     setMR(uint16 val);


/***********************************
 * COMMON Register Access Function *
 ***********************************/

/**
 * It gets IR value
 */
uint16   getIR(void);

/**
 * It sets IR value
 */
void     setIR(uint16 val);

/**
 * It gets IMR value
 */
uint16   getIMR(void);

/**
 * It sets IMR value
 */
void     setIMR(uint16 mask);

/**
 * It gets the source hardware address
 */
void     getSHAR(uint8 * addr);

/**
 * It sets the source hardware address
 */
void     setSHAR(uint8 * addr);

/**
 * It gets the gateway IP address
 */
void     getGAR(uint8 * addr);

/**
 * It sets the gateway IP address
 */
void     setGAR(uint8 * addr);    // set gateway address

/**
 * It gets the subnet mask address
 */
void     getSUBR(uint8 * addr);

/**
 * It sets the subnet mask address to global variable
 */
void     setSUBR(uint8 * addr); // set subnet mask address

/**
 * It sets the subnet mask address from global variable
 */
void     ApplySubnet(); // set subnet mask address to SUBR

/**
 * It sets the subnet mask address "0.0.0.0"
 */
void     ClearSubnet(); // set subnet mask address "0.0.0.0"

/**
 * It gets the source IP address
 */
void     getSIPR(uint8 * addr);

/**
 * It sets the source IP address
 */
void     setSIPR(uint8 * addr); // set local IP address

/**
 * It gets RTR value
 */
uint16   getRTR(void); 

/**
 * It sets RTR value
 */
void     setRTR(uint16 timeout); // set retry duration for data transmission, connection, closing ...

/**
 * It gets RCR value
 */
uint8    getRCR(void);
/**
 * It sets RCR value
 */
void     setRCR(uint8 retry); 

/**
 * It gets PATR value
 */
uint16   getPATR(void);

/**
 * It gets PTIMER value
 */
uint8    getPTIMER(void);

/**
 * It sets PTIMER value
 */
void     setPTIMER(uint8 time);

/**
 * It gets PMAGICR value
 */
uint8    getPMAGICR(void);

/**
 * It sets PTIMER value
 */
void     setPMAGICR(uint8 magic);

/**
 *  It gets PSIDR value
 */
uint16   getPSIDR(void);

/**
 *  It gets the PPPoE server hardware address
 */
void     getPDHAR(uint8* addr);

/**
 *  It gets the unreachable destination IP address of ICMP message.
 */
void     getUIPR(uint8* addr);

/**
 *  It gets the unreachable destination port number of ICMP message.
 */
uint16   getUPORTR(void);

/**
 *  It gets the fragmented MTU value of ICMP message.
 */
uint16   getFMTUR(void);

/**
 *  It gets Pn_BRDYR value.
 */
uint8    getPn_BRDYR(uint8 p);

/**
 *  It sets Pn_BRDYR value.
 */
void     setPn_BRDYR(uint8 p, uint8 cfg);

/**
 *  It gets the buffer depth of PIN "BRDYn".
 */
uint16   getPn_BDPTHR(uint8 p);

/**
 *  It sets the buffer depth of PIN "BRDYn".
 */
void     setPn_BDPTHR(uint8 p, uint16 depth);

/**
 *  It gets the ID of W5300.
 */
uint16   getIDR(void);



/***********************************
 * SOCKET Register Access Function *
 ***********************************/

/**
 *  It gets Sn_MR value.
 */
uint16   getSn_MR(SOCKET s);

/**
 *  It sets Sn_MR value.
 */
void     setSn_MR(SOCKET s, uint16 mode); 

/**
 *  It gets Sn_CR value.
 */
uint8    getSn_CR(SOCKET s);
/**
 *  It sets Sn_CR value.
 */
void     setSn_CR(SOCKET s, uint16 com);

/**
 *  It gets Sn_IMR value.
 */
uint8    getSn_IMR(SOCKET s);

/**
 *  It sets Sn_IMR value.
 */
void     setSn_IMR(SOCKET s, uint8 mask);

/**
 *  It gets Sn_IR value.
 */
uint8    getSn_IR(SOCKET s);

/**
 *  It sets Sn_IR value.
 */
void     setSn_IR(SOCKET s, uint8 ir);

/**
 *  It gets Sn_SSR value.
 */
uint8    getSn_SSR(SOCKET s);

/**
 *  It gets Sn_DHAR value.
 */
void     getSn_DHAR(SOCKET s, uint8* addr);

/**
 *  It sets Sn_DHAR value.
 */
void     setSn_DHAR(SOCKET s, uint8* addr);

// M_15052008 : Delete this function.
/*
 *  It gets Sn_DPORTR value.
 */
//uint16   getSn_DPORTR(SOCKET s);

/**
 *  It sets Sn_DPORTR value.
 */
void     setSn_DPORTR(SOCKET s, uint16 port);

/**
 *  It gets Sn_DIPR value.
 */
void     getSn_DIPR(SOCKET s, uint8* addr);

/**
 *  It sets Sn_DIPR value.
 */
void     setSn_DIPR(SOCKET s, uint8* addr);

/**
 *  It gets Sn_MSSR value.
 */
uint16   getSn_MSSR(SOCKET s);

/**
 *  It sets Sn_MSSR value.
 */
void     setSn_MSSR(SOCKET s, uint16 mss);

/**
 *  It gets Sn_KPALVTR value.
 */
uint8    getSn_KPALVTR(SOCKET s);

/**
 *  It sets Sn_KPALVTR value.
 */
void     setSn_KPALVTR(SOCKET s, uint8 time);

/**
 *  It gets Sn_TX_WRSR value.
 */
uint32   getSn_TX_WRSR(SOCKET s);

/**
 *  It gets Sn_KPALVTR value.
 */
void     setSn_TX_WRSR(SOCKET s, uint32 size);

/**
 *  It gets Sn_TX_FSR value.
 */
uint32   getSn_TX_FSR(SOCKET s);

/**
 *  It gets Sn_RX_RSR value.
 */
uint32   getSn_RX_RSR(SOCKET s);

/**
 *  It sets Sn_TX_FIFOR value.
 */
void     setSn_TX_FIFOR(SOCKET s, uint16 data);

/**
 *  It gets Sn_RX_FIFOR value.
 */
uint16   getSn_RX_FIFOR(SOCKET s);

/**
 *  It gets Sn_PROTOR value.
 */
uint8    getSn_PROTOR(SOCKET s);

/**
 *  It sets Sn_PROTOR value.
 */
void     setSn_PROTOR(SOCKET s, uint8 pronum);

/**
 *  It gets Sn_TOSR value.
 */
uint8    getSn_TOSR(SOCKET s);

/**
 *  It sets Sn_TOSR value.
 */
void     setSn_TOSR(SOCKET s, uint8 tos);

/**
 *  It gets Sn_TTLR value.
 */
uint8    getSn_TTLR(SOCKET s);

/**
 *  It sets Sn_TTLR value.
 */
void     setSn_TTLR(SOCKET s, uint8 ttl);

/**
 *  It gets Sn_FRAGR value.
 */
uint8    getSn_FRAGR(SOCKET s);
/**
 *  It sets Sn_FRAGR value.
 */
void     setSn_FRAGR(SOCKET s, uint8 frag);



/*******
 * ETC *
 *******/

/* Initialization & Interrupt request routine */

/**
 *  It initializes W5300.
 */
void     iinchip_init(void); 

/**
 *  It handles the interrupt of W5300.
 */
#ifdef __DEF_IINCHIP_INT__
   void     iinchip_irq(void);
#endif


/* Interanl memory operation */

/**
 *  It allocate internal TX/RX meory of each SOCKET.
 */
uint8    sysinit(uint8* tx_size, uint8* rx_size); // setting tx/rx buf size


/**
 *  It copies data to interna TX memory
 */
uint32   wiz_write_buf(SOCKET s,uint8* buf,uint32 len);


/**
 *  It copies data to your buffer from interna RX memory
 */
uint32   wiz_read_buf(SOCKET s, uint8* buf,uint32 len);


/**
 *  It gets the max size of internal TX memory of each SOCKET
 */
uint32   getIINCHIP_TxMAX(SOCKET s);

/**
 *  It gets the max size of internal RX memory of each SOCKET
 */
uint32   getIINCHIP_RxMAX(SOCKET s);



#ifdef __DEF_IINCHIP_PPP__
   /**
    *  It initializes to PPPoE of W5300
    */
   uint8    pppinit(uint8 *id, uint8 idlen, uint8 *passwd, uint8 passwdlen);
   /**
    *  It terminates PPPoE connection 
    */   
   void    pppterm(uint8 *mac, uint16 sessionid);
#endif

/**
 *  Delay function
 */
void  wait_1us(uint32 us);
/**
 *  Delay function
 */
void  wait_1ms(uint32 ms);
/**
 *  Delay function
 */
void  wait_10ms(uint32 ms);





#define SDRAM_BASE        0xA0000000

//Interrupt Control Registers
#define INTERRUPT_CONTROL_BASE 0x40D00000

#define ICIP              0x00
#define ICMR              0x04
#define ICLR              0x08
#define ICFP              0x0C
#define ICPR              0x10
#define ICCR              0x14

#define CLOCK_MANAGER_BASE 0x41300000

#define CCCR              0x00
#define CKEN              0x04
#define OSCC              0x08


#define CCCR_VALUE        0x00000241		// 400 MHz
//#define CCCR_VALUE        0x00000161		// TEST
//#define CCCR_VALUE        0x00000461		// TEST
//#define CCCR_VALUE        0x000001C1		// |0001|1100|0001 0x1C1

#define CKEN_VALUE        0x00000040
#define OSCC_VALUE        0x00000002//0x00000002

#define OSCR              0x40A00010
#define CLK_TO_10MS	  36864         // 3.686400 Mhz

//GPIO registers
#define GPIO_BASE         0x40E00000

#define GPLR0             0x00
#define GPLR1             0x04
#define GPLR2             0x08
#define GPDR0             0x0C
#define GPDR1             (*((volatile ulong *)(GPIO_BASE+0x10)))
#define GPDR2             0x14
#define GPSR0             0x18
#define GPSR1             0x1C
#define GPSR2             0x20
#define GPCR0             0x24
#define GPCR1             0x28
#define GPCR2             0x2C
#define GRER0             0x30
#define GRER1             0x34
#define GRER2             0x38
#define GFER0             0x3C
#define GFER1             0x40
#define GFER2             0x44
#define GDER0             0x48
#define GDER1             0x4C
#define GDER2             0x50
#define GAFR0_L           0x54
#define GAFR0_U           0x58
#define GAFR1_L           (*((volatile ulong *)(GPIO_BASE+0x5C)))
#define GAFR1_U           0x60
#define GAFR2_L           0x64
#define GAFR2_U           0x68

//GPIO initial values
#define GPDR0_VALUE       0xC0439330//0xC05BE830//0xC05BB130//0xC05B91F0
#define GPDR1_VALUE       0xFCFFAB82
#define GPDR2_VALUE       0x0001FFFF

#define GPSR0_VALUE       0x00408030//0x00588020//00588030//0x00588020
#define GPSR1_VALUE       0x00BFA882
#define GPSR2_VALUE       0x0001C000

#define GPCR0_VALUE       0xC0031100//0xC0033110//0xC00311D0
#define GPCR1_VALUE       0xFC400300
#define GPCR2_VALUE       0x00003FFF

#define GRER0_VALUE       0x0F800000
#define GRER1_VALUE       0x00000001
#define GRER2_VALUE       0x0020000C

#define GFER0_VALUE       0x00000000
#define GFER1_VALUE       0x00000000
#define GFER2_VALUE       0x00004001

#define GAFR0L_VALUE      0x80000000
#define GAFR0U_VALUE      0xA5000010
#define GAFR1L_VALUE      0x60008018
#define GAFR1U_VALUE      0xAAA5AAAA
#define GAFR2L_VALUE      0xAAA0000A
#define GAFR2U_VALUE      0x00000002

//Memory Control Registers
#define MEM_CTL_BASE      0x48000000

#define MDCNFG            0x00
#define MDREFR            0x04
#define MSC0              0x08
#define MSC1              0x0C
#define MSC2              0x10
#define MECR              0x14
#define SXCNFG            0x1C
#define MCMEM0            0x28
#define MCMEM1            0x2C
#define MCATT0            0x30
#define MCATT1            0x34
#define MCIO0             0x38
#define MCIO1             0x3C
#define MDMRS             0x40

//Memory Control Register initial values
#define MDCNFG_VALUE      0x00001AC9//0x0B000BC9
#define MDREFR_VALUE      0x020DF016//0x03CDF016//0x000BC018//0x00038016

#define MSC0_VALUE        0x7FF83FF0//0xFFF03FF0//0x23F223F2//0x3FF83FF0

#define MSC1_VALUE        0x12BC5554//0x12BC8240//0x5AA85AA8
#define MSC2_VALUE        0x7FF97FF1//0x7FF17FF1//0x24482448
#define MECR_VALUE        0x00000000//0x00000002
#define SXCNFG_VALUE      0x00000000//0x40484048
#define MCMEM0_VALUE      0x00010504//0x00020308
#define MCMEM1_VALUE      0x00010504//0x00020308
#define MCATT0_VALUE      0x00010504//0x00020308
#define MCATT1_VALUE      0x00010504//0x00020308
#define MCIO0_VALUE       0x00004715//0x00020308
#define MCIO1_VALUE       0x00004715//0x00020308
#define MDMRS_VALUE       0x00000000

#define FLYCNFG_VALUE     0x01FE01FE

// Power management
#define RCSR              0x40F00030
#define RCSR_SLEEP        0x00000004
#define PSPR              0x40F00008
#define PSSR              0x40F00004
#define PSSR_PH           0x00000010
#define PSSR_RDH          0x00000020
#define PSSR_STATUS_MASK  0x00000007


#define LCCR0       0x44000000	  	/* LCD Controller Control Register 0 */
#define LCCR1       0x44000004  	/* LCD Controller Control Register 1 */
#define LCCR2       0x44000008  	/* LCD Controller Control Register 2 */
#define LCCR3       0x4400000C  	/* LCD Controller Control Register 3 */
#define DFBR0       0x44000020  	/* DMA Channel 0 Frame Branch Register */
#define DFBR1       0x44000024  	/* DMA Channel 1 Frame Branch Register */


#define DCSR(n)                 (*((volatile ulong *)(0x40000000 + n*4)))
#define DSADR(n)                (*((volatile ulong *)(0x40000204 + n*0x10)))
#define DTADR(n)                (*((volatile ulong *)(0x40000208 + n*0x10)))
#define DCMD(n)                 (*((volatile ulong *)(0x4000020C + n*0x10)))

#define DCSR_RUN                 (1<<31)
#define DCSR_NODESC              (1<<30)
#define DCSR_IRQEN               (1<<29)
#define DCSR_REQPEN              (1<<8)
#define DCSR_STOPSTAT            (1<<3)
#define DCSR_ENDINT              (1<<2)
#define DCSR_STARINTR            (1<<1)
#define DCSR_BUSERRINTR          (1)

#define DCMD_INCSRC              (1<<31)
#define DCMD_INCTGT              (1<<30)
#define DCMD_FLOWSRC             (1<<29)
#define DCMD_FLOWTGT             (1<<28)
#define DCMD_ENDIRQEN            (1<<21)
#define DCMD_NOENDIAN            (1<<18)
#define DCMD_BUST8               (1<<16)
#define DCMD_BUST16              (2<<16)
#define DCMD_BUST32              (3<<16)
#define DCMD_BUSW8               (1<<14)
#define DCMD_BUSW16              (2<<14)
#define DCMD_BUSW32              (3<<14)
#define DCMD_LEN(N)              (N & 0x1FFE) // MAX 8K -2 

#define DMA_MAX_LEN              (8190) 

/**********************************
 * define function of SOCKET APIs * 
 **********************************/

/**
 * Open a SOCKET.
 */ 
uint8    socket(SOCKET s, uint8 protocol, uint16 port, uint16 flag);

/**
 * Close a SOCKET.
 */ 
void     close(SOCKET s);                                                           // Close socket

/**
 * It tries to connect a client.
 */
uint8    connect(SOCKET s, uint8 * addr, uint16 port);

/**
 * It tries to disconnect a connection SOCKET with a peer.
 */
void     disconnect(SOCKET s); 

/**
 * It is listening to a connect-request from a client.
 */
uint8    listen(SOCKET s);	    

/**
 * It sends TCP data on a connection SOCKET
 */
uint32   send(SOCKET s, uint8 * buf, uint32 len);


/**
 * It receives TCP data on a connection SOCKET
 */
uint32   recv(SOCKET s, uint8 * buf, uint32 len);

/**
 * It sends UDP, IPRAW, or MACRAW data 
 */
uint32   sendto(SOCKET s, uint8 * buf, uint32 len, uint8 * addr, uint16 port); 

/**
 * It receives UDP, IPRAW, or MACRAW data
 */
uint32   recvfrom(SOCKET s, uint8 * buf, uint32 len, uint8 * addr, uint16  *port);

#define SERIAL_SPEED			0x08
#define SERIAL_DOWNLOAD_SPEED		0x08


#define FFUART_BASE		0x40100000
#define FFRBR			(*((volatile ulong *)(FFUART_BASE+0x00)))
#define FFTHR           (*((volatile ulong *)(FFUART_BASE+0x00)))
#define FFIER          	(*((volatile ulong *)(FFUART_BASE+0x04)))
#define FFIIR          	(*((volatile ulong *)(FFUART_BASE+0x08)))
#define FFFCR          	(*((volatile ulong *)(FFUART_BASE+0x08)))
#define FFLCR          	(*((volatile ulong *)(FFUART_BASE+0x0C)))
#define FFMCR          	(*((volatile ulong *)(FFUART_BASE+0x10)))
#define FFLSR          	(*((volatile ulong *)(FFUART_BASE+0x14)))
#define FFMSR          	(*((volatile ulong *)(FFUART_BASE+0x18)))
#define FFSPR          	(*((volatile ulong *)(FFUART_BASE+0x1C)))
#define FFISR          	(*((volatile ulong *)(FFUART_BASE+0x20)))
#define FFDLL          	(*((volatile ulong *)(FFUART_BASE+0x00)))
#define FFDLH          	(*((volatile ulong *)(FFUART_BASE+0x04)))

#define SERIAL_BAUD_115200 (0x00000008)


void SerialInit(ulong);
void SerialOutputByte(const char);
int SerialInputByte(char *);

/* MD5 context. */
typedef struct {
        uint32 state[4];    /* state (ABCD)                            */
        uint32 count[2];    /* number of bits, modulo 2^64 (lsb first) */
        uint8  buffer[64];  /* input buffer                            */
      } md5_ctx;

extern void md5_init(md5_ctx *context);
extern void md5_update(md5_ctx *context, uint8 *buffer, uint32 length);
extern void md5_final(uint8 result[16], md5_ctx *context);

#define ADDR32(A)			(*((volatile ulong *)(A)))
#define ADDR16(A)			(*((volatile ushort *)(A)))
#define ADDR8(A)			(*((volatile uchar *)(A)))

typedef struct {
	long	terminalSpeed;
	long	downloadSpeed;
} LOADER_STATUS;

// Byte swapping.
#define SWAP8(A)		(A)
#define SWAP16(A)		((((A << 8 ) & 0xFF00)) | ((A >> 8)& 0x00FF))
#define SWAP32(A)		((((A<<24)&0xFF000000)) | (((A<<8)&0x00FF0000)) | (((A>>8)&0x0000FF00)) | (((A>>24)&0x000000FF)))


#define NEWLINE					"\n"

extern LOADER_STATUS	status;

void	MemCpy32(void *dest, void *src, int numWords);
void	HexDump(char *addr, int len);

int		StrCmp(char *s1, char *s2);
int		StrNCmp(char *s1, char *s2, int len);
void	MemCpy(void *dest, void *src, int len);
void	MemSet(void *dest, const char c, int len);
int		MemCmp(void *addr1, void *addr2, int len);
void	StrCpy(char *dest, char *src);
int		StrLen(char *str);

//bool	HexToInt(char *s, void *retval, VAR_TYPE type);
int		DecToLong(char *s, long *retval);

void	printf(char *fmt, ...);

void     loopback_tcps(SOCKET s, uint16 port, uint16 mode);
void     loopback_tcpc(SOCKET s, uint8* addr, uint16 port, uint8* buf,uint16 mode);
void     loopback_udp(SOCKET s, uint16 port, uint8* buf, uint16 mode);


#endif



