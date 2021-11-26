/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    rwflash.c
 * @brief   Flash Memory code.
 *
 * @addtogroup Storage
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "mem.h"
#include "spi_flash.h"
#include "user_interface.h"

#include "rwflash.h"

/**
 * @brief Global string variable for flash storage data
 * @details Somehow it can only one variable for each address
 *          and because I'm to lazy to calculate address space,
 *          so I use one address only
 */
char strConfigs[FLASH_CONFIGS_LEN];

/**
 * @brief Write value to Flash Memory sector
 * @param[in] Flash Memory sector
 * @param[in] Flash Memory data to write
 */
LOCAL void ICACHE_FLASH_ATTR rwflash_write(uint16 sec,uint32 *src){
    spi_flash_erase_sector(sec);
    spi_flash_write(sec * SPI_FLASH_SEC_SIZE, src, 4*sizeof(src));
}

/**
 * @brief Read value to Flash Memory sector
 * @param[in] Flash Memory sector
 * @param[in] Flash Memory buffer read
 */
LOCAL void ICACHE_FLASH_ATTR rwflash_read(uint16 sec,uint32 *des){
    spi_flash_read(sec * SPI_FLASH_SEC_SIZE, des, 4*sizeof(des));
}

/**
 * @brief Empty String from Flash Read
 * @details Empty if character at 0, 1, and 2 are 255
 * @param[in] String data to check and emptying
 * @return String data length
 */
LOCAL uint8 ICACHE_FLASH_ATTR rwflash_strchk_empty(char *strData){
    uint8 strDataLen;

    if(os_strlen(strData)<=3){
        strDataLen = 0;
        os_printf("String data too short\r\n");
    }
    else{
        if(strData[0]==255 && strData[1]==255 && strData[2]==255){
            strDataLen = 0;
            os_printf("String data only null\r\n");
        }
        else{
            strDataLen = os_strlen(strData);
        }
    }

    return strDataLen;
}

void ICACHE_FLASH_ATTR rwflash_int_write(uint16 sec, uint16 *src){
    rwflash_write(sec, (uint32 *)src);
}

void ICACHE_FLASH_ATTR rwflash_int_read(uint16 sec, uint16 *des){
    rwflash_read(sec, (uint32 *)des);
}

void ICACHE_FLASH_ATTR rwflash_str_write(uint16 sec, char *src){
    os_printf("Write String: %s\r\n",src);
    rwflash_write(sec, (uint32 *)src);
}

void ICACHE_FLASH_ATTR rwflash_str_read(uint16 sec, char *des){
    rwflash_read(sec, (uint32 *)des);
    os_printf("Read String: %s\r\n",des);
}

void ICACHE_FLASH_ATTR rwflash_conf_parse(char *strIN, char *strOUT, uint8 num){
    char strInput[FLASH_CONFIGS_LEN];
    char strSplit[FLASH_CONFIGS_NUM][FLASH_CONFIGS_LEN/FLASH_CONFIGS_NUM];
    uint8 i,j,cnt,dataLen;

    dataLen=rwflash_strchk_empty(strIN);

    if(dataLen>0){
        os_strcpy(strInput,strIN);
        j=0; cnt=0;
        for(i=0;i<=os_strlen(strInput);i++){
            if(strInput[i]==' ' || strInput[i]=='\0' || strInput[i]=='/'){
                strSplit[cnt][j]='\0';
                cnt++;
                j=0;
            }
            else {
                strSplit[cnt][j]=strInput[i];
                j++;
            }
        }
        os_strcpy(strOUT,strSplit[num]);
    }
    else{
        os_strcpy(strOUT,"");
    }
}

/** @} */
