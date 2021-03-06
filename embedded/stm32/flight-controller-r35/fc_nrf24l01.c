/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#include "ch.h"
#include "hal.h"

#include <string.h>

#include "fc_uart.h"
#include "fc_spi.h"
#include "fc_nrf24l01.h"
#include "fc_gpio.h"

/*
 * Binary semaphore, to lock access to the send and receive queue of the NRF24L01
 */
BinarySemaphore NRFSemIRQ;
Semaphore	NRFSemRX;
Semaphore	NRFSemTX;

/*
 * Status flags
 */
typedef struct {
	uint8_t maxRt; /* Set the flag when the max retransmit is reached. */
} NRFStatStruct;
static NRFStatStruct NRFStatus;

/*
 * Flag enum for the PRIM_RX flag.
 */
typedef enum {prim_tx=0, prim_rx} primEnum;

/*
 * Logical states
 */
typedef enum {low=0, high} boolEnum;

/*
 * The number of bytes the NRF24L01 RX FIFO is going to hold
 * This can be 32 bytes MAX
 */
#define NRF_FIFO_BYTES 32

/*
 * The following commands and registers are derived from the NRF24L01 Datasheet
 */

/*
 * NRF24L01 commands
 */
#define NRF_COM_READREG							0b00000000	/* 0b000A AAAA read register  A AAAA	*/
#define NRF_COM_WRITEREG						0b00100000	/* 0b001A AAAA write register A AAAA	*/
#define NRF_COM_RX_PAYLOAD					0b01100001  /* Read RX-payload										*/
#define NRF_COM_TX_PAYLOAD					0b10100000  /* Write TX-payload										*/
#define NRF_COM_FLUSH_TX						0b11100001	/* Flush TX FIFO											*/
#define NRF_COM_FLUSH_RX						0b11100010	/* Flush RX FIFO											*/
#define NRF_COM_REUSE_TX						0b11100011  /* Reuse last transmitted payload			*/
#define NRF_COM_ACTIVATE						0b01010000  /* Activate the features							*/
#define NRF_COM_R_RX_PL_WID					0b01100000	/* Read RX-payload width							*/
#define NRF_COM_W_ACK_PAYLOAD				0b10101000	/* 0b10101PPP valid from 000 to 101		*/
#define NRF_COM_W_TX_PAYLOAD_NOACK	0b10110000	/* Disables AUTOACK on packet					*/
#define NRF_COM_NOP									0b11111111	/* NOP (No operation)									*/

/*
 * NRF24L01 registers
 */
#define NRF_REG_CONFIG							0x00				/* Configuration Register							*/
#define NRF_REG_EN_AA								0x01				/* Auto Acknowledgment								*/
#define NRF_REG_EN_RXADDR						0x02				/* Enabled RX Addresses								*/
#define NRF_REG_SETUP_AW						0x03				/* Setup of Address Widths						*/
#define	NRF_REG_SETUP_RETR					0x04				/* Setup of Automatic Retransmission	*/
#define NRF_REG_RF_CH								0x05				/* RF Channel													*/
#define NRF_REG_RF_SETUP						0x06				/* RF Setup Register									*/
#define NRF_REG_STATUS							0x07				/* Status Register										*/
#define NRF_REG_OBSERVE_TX					0x08				/* Transmit observe register					*/
#define NRF_REG_CD									0x09				/* Carrier Detect											*/
#define NRF_REG_RX_ADDR_P0					0x0A				/* Receive address data pipe 0				*/
#define NRF_REG_RX_ADDR_P1					0x0B				/* Receive address data pipe 1				*/
#define NRF_REG_RX_ADDR_P2					0x0C				/* Receive address data pipe 2				*/
#define NRF_REG_RX_ADDR_P3					0x0D				/* Receive address data pipe 3				*/
#define NRF_REG_RX_ADDR_P4					0x0E				/* Receive address data pipe 4				*/
#define NRF_REG_RX_ADDR_P5					0x0F				/* Receive address data pipe 5				*/
#define NRF_REG_TX_ADDR							0x10				/* Transmit address										*/
#define NRF_REG_RX_PW_P0						0x11				/* Number of bytes in RX payload			*/
#define NRF_REG_RX_PW_P1						0x12				/* Number of bytes in RX payload			*/
#define NRF_REG_RX_PW_P2						0x13				/* Number of bytes in RX payload			*/
#define NRF_REG_RX_PW_P3						0x14				/* Number of bytes in RX payload			*/
#define NRF_REG_RX_PW_P4						0x15				/* Number of bytes in RX payload			*/
#define NRF_REG_RX_PW_P5						0x16				/* Number of bytes in RX payload			*/
#define NRF_REG_FIFO_STATUS					0x17				/* FIFO Status Register								*/
#define NRF_REG_DYNPD								0x1C				/* Enable dynamic payload length			*/
#define NRF_REG_FEATURE							0x1D				/* Feature Register										*/

/*
 * Status register masks
 */
#define NRF_STAT_RX_DR							0b01000000	/* Data ready RX FIFO interrupt				*/ 
#define NRF_STAT_TX_DS							0b00100000	/* Data sent interrupt								*/
#define NRF_STAT_MAX_RT							0b00010000	/* Maximum number of TX retries				*/
#define NRF_STAT_RX_R_NO						0b00001110	/* Data pipe number for payload				*/
#define NRF_STAT_TX_FULL						0b00000001	/* TX FIFO full flag									*/

/*
 * FIFO status mask
 */
#define NRF_FIFO_TX_REUSE						0b01000000	/* Reuse lost sent data packet high		*/
#define NRF_FIFO_TX_FULL						0b00100000	/* TX FIFO full flag									*/
#define NRF_FIFO_TX_EMPTY						0b00010000	/* TX FIFO empty flag									*/
#define NRF_FIFO_RX_FULL						0b00000010	/* RX FIFO full flag									*/
#define NRF_FIFO_RX_EMPTY						0b00000001	/* RX FIFO empty flag									*/

/*
 * Buffers
 */
#define NRF_BUF_SIZE 64
static uint8_t txbuf[NRF_BUF_SIZE];
static uint8_t rxbuf[NRF_BUF_SIZE];

/*
 * Flag to signal if init is done
 */
uint8_t NRFInitDone;

/*
 * Reverse buffer (Used to reverse addresses)
 */
static void NRFReverseBuf(uint8_t in[], uint8_t out[], size_t size)
{
	size_t count=0;

	for(count=0; count < size; count++){
		out[count]=in[size-(count+1)];
	}
}

/*
 * Set CE to high/low
 * 0 sets pin low, 1 sets pin high
 */
static void NRFSetCE(boolEnum state)
{
	if(state == low){
		palClearPad(NRF_PORT_CE_IRQ, NRF_PORT_CE);
	} else {
		palSetPad(NRF_PORT_CE_IRQ, NRF_PORT_CE);
	}
}

/*
 * Write byte to register
 */
static void NRFWriteReg(uint8_t reg, uint8_t val[], uint8_t size)
{
	/*
	 * create command
	 */
	txbuf[0]=(NRF_COM_WRITEREG | reg);
	memcpy(txbuf+1, val, size);

	/*
	 * Send command and payload
	 */
	SPISendData(&SPID1, txbuf, size+1);
}

/*
 * Write byte to register
 */
static void NRFWriteSingleReg(uint8_t reg, uint8_t val)
{
	NRFWriteReg(reg, &val, 1);
}

/*
 * Set channel 
 * Frequency is F0= 2400 + RF_CH [MHz]
 */
void NRFSetChannel(uint8_t chan)
{
	NRFWriteReg(NRF_REG_RF_CH, &chan, 1); 
}

/*
 * Set the address to the receiver pipe
 * Normaly pipe  is used to receive the ack packets by shockburst
 * Use pipe 1 as the first data receive pipe
 * @Arguments
 * pipe				Pipe number to set the address to
 * addr_size	The size of the address in bytes
 * addr				Byte array holding the addr, LSB first
 */
void NRFSetRecvAddr(uint8_t pipe, uint8_t addr[], uint8_t addrSize)
{
	uint8_t nrfCommand;
	uint8_t pipeAddr[5]={'\0'};

	/*
	 * CE to low When configuring
	 */
	NRFSetCE(high);
	chThdSleepMilliseconds(1);

	/*
	 * Create command
	 */
	nrfCommand=NRF_REG_RX_ADDR_P0 + pipe;

	/*
	 * As lsb needs to be sent first, reverse the address order.
	 */
	NRFReverseBuf(addr, pipeAddr, addrSize);

	/*
	 * Set address
	 */
	NRFWriteReg(nrfCommand, pipeAddr, addrSize);
}

/*
 * Set the address to the receiver pipe
 * @Arguments
 * pipe				Pipe number to set the address to
 * addr_size	The size of the address in bytes
 * addr				Byte array holding the address, LSB first
 */
void NRFSetSendAddr(uint8_t addr[], uint8_t addrSize)
{
	uint8_t nrfCommand;
	uint8_t pipeAddr[5]={'\0'};

	/*
	 * CE to low When configuring
	 */
	NRFSetCE(high);

	/*
	 * As lsb needs to be sent first, reverse the address order.
	 */
	NRFReverseBuf(addr, pipeAddr, addrSize);

	/*
	 * Set pipe 0 address identical to send address,
	 * this to enable the automatic shockburst handling of ack's
	 */
	nrfCommand=NRF_REG_RX_ADDR_P0;
	NRFWriteReg(nrfCommand, pipeAddr, addrSize);

	/*
	 * Set the TX pipe address
	 */
	nrfCommand=NRF_REG_TX_ADDR;
	NRFWriteReg(nrfCommand, pipeAddr, addrSize);
}

/*
 * Get Status from inside interrupt routine
 */
static uint8_t NRFGetStatus(void)
{
	uint8_t command[2];
	uint8_t result[2];
	
	/*
	 * Set NOP and receive the STATUS register
	 */
	command[0]=NRF_COM_NOP;
	SPIExchangeData(&SPID1, command, result, 2);

	return result[0];
}

/*
 * Get config from inside interrupt routine
 */
static uint8_t NRFGetConfig(void)
{
	uint8_t command[2];
	uint8_t result[2];
	
	/*
	 * Set NOP and receive the STATUS register
	 */
	command[0]=NRF_COM_READREG | NRF_REG_CONFIG;
	SPIExchangeData(&SPID1, command, result, 2);

	return result[1];
}

/*
 * Get config from inside interrupt routine
 */
static void NRFSetConfig(uint8_t config)
{
	/*
	 * Write to the config register.
	 */
	NRFWriteSingleReg(NRF_REG_CONFIG, config);
}

/*
 * Reset status flags inside interrupt routine
 */
static void NRFResetStatus(uint8_t statMask)
{
	uint8_t command[2];
	uint8_t result[2];
	
	/*
	 * Set NOP and receive the STATUS register
	 */
	command[0]=NRF_COM_WRITEREG | NRF_REG_STATUS;
	command[1]=statMask;
	SPIExchangeData(&SPID1, command, result, 2);
}

/*
 * Flush the TX Queue
 */
void NRFFlushTX(void)
{
	uint8_t command;
	uint8_t result;
	
	/*
	 * Set NOP and receive the STATUS register
	 */
	command=NRF_COM_FLUSH_TX;
	SPIExchangeData(&SPID1, &command, &result, 1);
}

/*
 * Set Reset PRIM_RX in CONFIG register.
 * State 1 for on, 0 for off.
 */
static void NRFSetPrimRx(primEnum state)
{
	uint8_t config=0;
	
	/*
	 * Get config register.
	 */
	config = NRFGetConfig();

	/*
	 * Change PRIM_RX flag
	 * 0 is clear bit, 1 is set bit
	 */
	if(state == prim_tx){
		config &= 0b11111110;
	} else {
		config |= 0b00000001;
	}

	/*
	 * Set config register
	 */
	NRFSetConfig(config);
}

/*
 * Handle the IRQ signal, unlock the Semaphores or set flags. 
 */
void NRFHandleIrq(void)
{
	uint8_t	status=0;

	/*
	 * Wait for the semaphore
	 */
	chBSemWait(&NRFSemIRQ);

	/*
	 * Execute NOP to retrieve the status register
	 */
	status = NRFGetStatus();

	/*
	 * Data ready in FIFO
	 * Signal semaphore data can be retrieved
	 */
	if((NRF_STAT_RX_DR & status) != 0){
		chSemSignal(&NRFSemRX);
	}

	/*
	 * Max number of TX retries, set flag
	 * Also clear flag or no further communication is possible
	 */
	if((NRF_STAT_MAX_RT & status) != 0){
		/*
		 * Set the MAX TX flag
		 * Flush out the queue, because we can't send them anyway.
		 */
		NRFStatus.maxRt=1;
		NRFFlushTX();

		/*
		 * Signal the semaphore because sending has failed
		 */
		chSemSignal(&NRFSemTX);
	}

	/*
	 * Called when the TX_FIFO is full
	 * Take TX semaphore, until a data sent interrupt signals the semaphore again
	 */
	if((NRF_STAT_TX_FULL & status) != 0){
		/*
		 * Lock the semaphore, because the TX queue is full
		 */
		chSemWait(&NRFSemTX);
	} else {
		/*
		 * TX Queue not full.
		 */
		chSemSignal(&NRFSemTX);
	}

	/*
	 * Reset the asserted interrupt flags in the register
	 */
	NRFResetStatus(status);
}

/*
 * Routine to unlock IRQ handling.
 */
void NRFReportIRQ(void)
{
	if(NRFInitDone == 1) {
		/*
		 * Unlock the IRQ Semaphore
		 */
		chBSemSignalI(&NRFSemIRQ);
	}
}

/*
 * NRF read RX FIFO
 */
static void NRFReadRXFifo(uint8_t *outBuf)
{
	uint8_t command=0;
	uint8_t inBuf[NRF_FIFO_BYTES+1];

	/*
	 * Build command and send retreive RX command to NRF24L01
	 */
	command = NRF_COM_RX_PAYLOAD;
	SPIExchangeData(&SPID1, &command, inBuf, NRF_FIFO_BYTES+1);

	memcpy(outBuf, inBuf+1, NRF_FIFO_BYTES);
}

/*
 * NRF read RX FIFO
 */
static void NRFWriteTXFifo(uint8_t *inBuf)
{
	uint8_t command[33];
	uint8_t bogus[33];

	/*
	 * Build command and send retrieve RX command to NRF24L01
	 */
	command[0] = NRF_COM_TX_PAYLOAD;
	memcpy(command+1, inBuf, NRF_FIFO_BYTES);
	SPIExchangeData(&SPID1, command, bogus, NRF_FIFO_BYTES);
}

/*
 * NRF RX FIFO empty
 * Returns FALSE if full, TRUE if empty
 */
static uint8_t NRFRXFifoEmpty(void)
{
	uint8_t command[2];
	uint8_t	result[2];

	/*
	 * Build command to read status register
	 */
	command[0] = NRF_COM_READREG | NRF_REG_FIFO_STATUS;
	SPIExchangeData(&SPID1, command, result, 2);

	if((result[1] & NRF_FIFO_RX_EMPTY) != 0) {
		return TRUE; /* FIFO empty */
	} else {
		return FALSE;
	}
}

/*
 * Function to receive data from FIFO
 * This functions blocks until data is available
 * The output buffer needs to be NRF_FIFO_BYTES(32) bytes wide
 */
void NRFReceiveData(uint8_t *pipeNr, uint8_t *inBuf)
{
	//msg_t		statusSem=RDY_RESET;
	uint8_t statusReg=0;
	//uint8_t configReg=0;

	/*
	 * Set PRIM_RX register.
	 */
	NRFSetPrimRx(prim_rx);

	/*
	 * Set NRF24L01 to receive mode.
	 * This takes about 1.3 ms
	 */
	NRFSetCE(high);

	/*
	 * Wait for binary semaphore NRFSemRX
	 */
	chSemWait(&NRFSemRX);

	/*
	 * Bring CE down, in order to execute the read operation
	 */
	NRFSetCE(low);

	/*
	 * Get the status register and distill the RX PIPE number
	 */
	statusReg = NRFGetStatus();
	*pipeNr  = (statusReg & NRF_STAT_RX_R_NO) >> 1;

	/*
	 * Retreive data from fifo
	 */
	NRFReadRXFifo(inBuf);

	/*
	 * Bring CE down, in order to execute the read operation
	 */
	NRFSetCE(high);

	/*
	 * When there is still data in the pipe 1, 
	 * signal the semaphore
	 * When the FIFO is empty the semaphore stays taken until the next interrupt
	 */
	if(NRFRXFifoEmpty() == FALSE) {
		chSemSignal(&NRFSemRX);
	}
}

/*
 * Function to send data
 * This functions blocks until data is available
 * The send output buffer needs to be NRF_FIFO_BYTES(32) bytes wide
 */
void NRFSendData(uint8_t *outBuf)
{
	/*
	 * Set PRIM_RX register.
	 */
	NRFSetPrimRx(prim_tx);

	/*
	 * Wait for semaphore NRFSemTX
	 */
	chSemWait(&NRFSemTX);

	/*
	 * Put CE high
	 */
	NRFSetCE(high);
	chThdSleepMilliseconds(1);

	/*
	 * Send the data to pipe 1 (the out pipe)
	 */
	NRFWriteTXFifo(outBuf);
}

static void NRFPrintAddrs(void)
{
	uint8_t rxaddr[5];

	/*
	 * DEBUG, try to read a register, and display the result
	 */
	memset(rxbuf, 0, NRF_BUF_SIZE);
	txbuf[0]=(NRF_COM_READREG | NRF_REG_TX_ADDR);
	SPIExchangeData(&SPID1, txbuf, rxbuf, 6);
	NRFReverseBuf(rxbuf+1, rxaddr, 5);
	UARTPrintf( "TX Address 0x%x%x%x%x%x\r\n", rxaddr[0], rxaddr[1], rxaddr[2], rxaddr[3], rxaddr[4]); // DEBUG 


	/*
	 * DEBUG, try to read the P0 address
	 */
	memset(rxbuf, 0, NRF_BUF_SIZE);
	txbuf[0]=(NRF_COM_READREG | NRF_REG_RX_ADDR_P0);
	SPIExchangeData(&SPID1, txbuf, rxbuf, 6);
	NRFReverseBuf(rxbuf+1, rxaddr, 5);
	UARTPrintf( "RX Address P0 0x%x%x%x%x%x\r\n", rxaddr[0], rxaddr[1], rxaddr[2], rxaddr[3], rxaddr[4]); // DEBUG 


	/*
	 * DEBUG, try to read the P0 address
	 */
	memset(rxbuf, 0, NRF_BUF_SIZE);
	txbuf[0]=(NRF_COM_READREG | NRF_REG_RX_ADDR_P1);
	SPIExchangeData(&SPID1, txbuf, rxbuf, 6);
	NRFReverseBuf(rxbuf+1, rxaddr, 5);
	UARTPrintf( "RX Address P1 0x%x%x%x%x%x\r\n", rxaddr[0], rxaddr[1], rxaddr[2], rxaddr[3], rxaddr[4]); // DEBUG 
}

/*
 * Test if there is a carrier signal active on the channel
 * When present return true
 */
uint8_t NRFCarrier(void)
{
	uint8_t command[2];
	uint8_t result[2];
	uint8_t out=0;
	
	/*
	 * Set NOP and receive the STATUS register
	 */
	command[0]=NRF_COM_READREG | NRF_REG_CD;
	SPIExchangeData(&SPID1, command, result, 2);

	/*
	 * Clean output signal.
	 */
	out = result[1] & 0b00000001;
	if(out == 1) {
		return TRUE;
	} 
	return FALSE;
}

/*
 * Flush RX
 */
static void NRFFlushRX(void)
{
	uint8_t command[1];
	uint8_t result[1];

	/*
	 * Set NOP and receive the STATUS register
	 */
	command[0]=NRF_COM_FLUSH_RX; 
	SPIExchangeData(&SPID1, command, result, 1);
}

/*
 * Initialize the NRF24L01 chip
 */
void NRFInit(void)
{
	/*
	 * Initialize the FIFO semaphores 
	 */
	chBSemInit(&NRFSemIRQ, TRUE);		/* Locks the thread until an IRQ arrives														*/
	chSemInit(&NRFSemRX, 0);		/* Semaphore initialized as taken, because no data is ready yet			*/ 
	chSemInit(&NRFSemTX, 1);		/* Semaphore initialized as free, because transmit channel is open	*/ 

	/*
	 * Setup the pad mode for the EC pin
	 * The IRQ pin is set in the Ext module.
	 */
	palSetPadMode(NRF_PORT_CE_IRQ, NRF_PORT_CE, PAL_MODE_OUTPUT_PUSHPULL);	/* EC, OUTPUT to change send/receive mode	*/

	/*
	 * CE Pin low before setting config
	 */
	NRFSetCE(low);
	chThdSleepMilliseconds(2);															/* It takes 1.5ms power down->standby	*/

	/*
	 * Set configuration registers
	 */
	NRFWriteSingleReg(NRF_REG_EN_RXADDR	, 0b00000011);			/* Enable data pipe 0,1								*/
	NRFWriteSingleReg(NRF_REG_EN_AA			, 0b00000011);			/* Enhanced ShockBurst on channel 0,1	*/
	NRFWriteSingleReg(NRF_REG_SETUP_AW	,	0b00000011);			/* 5 bytes address width							*/
	NRFWriteSingleReg(NRF_REG_SETUP_RETR, 0b00010011);			/* Up to 3 Re-Transmit, Wait 500??S		*/
	NRFWriteSingleReg(NRF_REG_RF_SETUP	, 0b00000111);			/* Sets up the channel we work on			*/
	NRFWriteSingleReg(NRF_REG_STATUS		, 0b00001110);			/* Reset the IRQ registers.						*/
	NRFWriteSingleReg(NRF_REG_RX_PW_P0	, NRF_FIFO_BYTES);	/* Pipe 0 FIFO holds 32 bytes.				*/
	NRFWriteSingleReg(NRF_REG_RX_PW_P1	, NRF_FIFO_BYTES);	/* Pipe 1 FIFO holds 32 bytes.				*/
	NRFWriteSingleReg(NRF_REG_CONFIG		, 0b00001110);			/* ENABLE CRC, POWER_UP								*/
	chThdSleepMilliseconds(2);															/* It takes 1.5ms power down->standby	*/

	/*
	 * Flush TX and RX
	 */
	NRFFlushTX();
	NRFFlushRX();

	NRFPrintAddrs();

	/*
	 * Set CE to high, to put NRF24L01 into Receive mode.
	 */
	NRFSetCE(high);
	chThdSleepMilliseconds(2);															/* It takes 1.5ms power down->standby	*/
	
	/*
	 * Switch modes 
	 */
	NRFSetPrimRx(prim_rx);
	chThdSleepMilliseconds(1);															/* It takes 1.5ms power down->standby	*/

	/*
	 * Interrupts are handled from this point on.
	 */
	NRFInitDone=1;
	NRFResetStatus(0x40);
}

/*
 * NRF24L01 test
 */
void NRFtest(void)
{
	//uint8_t data_out[33];
	//uint8_t	status=0;
	uint8_t sendAddr[5]={0xF0, 0xF0, 0xF0, 0xF0, 0xD2};
	uint8_t recvAddr[5]={0xF0, 0xF0, 0xF0, 0xF0, 0xE1};
	uint8_t pipeNr=0;
	uint8_t inBuf[32]={'\0'};

	/*
	 * Set device to channel 1
	 */
	NRFSetChannel(1);

	/*
	 * Setup address for send and receive pipe
	 */
	NRFSetSendAddr(sendAddr, 5);
	NRFSetRecvAddr(1, recvAddr, 5);

	NRFPrintAddrs();

	/*
	 * Main loop.
	 */
	while(1==1) {
		/*
		 * Wait for data to be received.
		 * Print pipenumber + content.
		 */
		UARTPrintf("Waiting for pkg..\r\n");
		NRFReceiveData(&pipeNr, inBuf);
		UARTPrintf("pipeNr[%d] msg: %s\r\n", pipeNr, inBuf);

#if 0
		/*
		 * Test sending packet
		 */
		memcpy(data_out, "Test 123\r\n", strlen("Test 123\r\n"));
		NRFSendData(data_out);
#endif

		/*
		 * Sleep and show we are still alive
		 */
		ledtoggle2();
    chThdSleepMilliseconds(100);
		//status = NRFGetStatus();
		//UARTPrintf("Status 0x%2.2x\r\n", status);
	}
}

