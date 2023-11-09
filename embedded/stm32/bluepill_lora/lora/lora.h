/**
 * @file lora.h
 * @brief LoRa module SPI header
 *
 * @addtogroup LORA
 * @{
 */


#ifndef _LORA_H_
#define _LORA_H_

// registers
#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_OCP                  0x0b
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_RSSI_VALUE           0x1b
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_FREQ_ERROR_MSB       0x28
#define REG_FREQ_ERROR_MID       0x29
#define REG_FREQ_ERROR_LSB       0x2a
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_INVERTIQ             0x33
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_INVERTIQ2            0x3b
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42
#define REG_PA_DAC               0x4d

// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06
#define MODE_CAD                 0x07

// PA config
#define PA_BOOST                 0x80

// IRQ masks
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40
#define IRQ_CAD_DONE_MASK          0x04
#define IRQ_CAD_DETECTED_MASK      0x01

#define RF_MID_BAND_THRESHOLD    525E6
#define RSSI_OFFSET_HF_PORT      157
#define RSSI_OFFSET_LF_PORT      164

#define MAX_PKT_LENGTH           255

// GPIOA5 -> SCK
// GPIOA6 -> MISO
// GPIOA7 -> MOSI
#define LORA_DEFAULT_NSS_PIN    4 // GPIOA4
#define LORA_DEFAULT_RESET_PIN  0 // GPIOB0
#define LORA_DEFAULT_DIO0_PIN   3 // GPIOA3 -> Synchronize pin, keep connected

#define PA_OUTPUT_RFO_PIN       0
#define PA_OUTPUT_PA_BOOST_PIN  1

#define GPIOA_SPI1NSS   4
#define USE_LOWER_SPI   TRUE

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

/**
 * @brief Initiate Module with specified frequency
 *
 * @param frequency
 */
void lora_begin(long frequency);

/**
 * @brief Set Module Frequency
 *
 * @param frequency
 */
void lora_setFrequency(long frequency);

/**
 * @brief Set Output Pin
 *
 * @param level
 * @param outputPin
 */
void lora_setTxPower(int level, uint8_t outputPin);

/**
 * @brief Packet Sending Begin
 *
 */
void lora_beginPacket(void);

/**
 * @brief Write characters
 *
 * @param buffer
 * @param size
 * @return size_t
 */
size_t lora_writeChars(char *buffer, size_t size);

/**
 * @brief Packet Sending End
 *
 */
void lora_endPacket(void);

uint16_t lora_parsePacket(void);
int lora_packetRssi(void);
int lora_available(void);
int lora_read(void);

#endif

/**  @} */

