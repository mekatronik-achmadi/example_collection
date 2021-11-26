/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/**
 * @file    drv_uart.c
 * @brief   GPIO 16 Driver code.
 *
 * @addtogroup Indicator
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "driver/uart.h"
#include "driver/uart_register.h"
#include "mem.h"
#include "os_type.h"
#include "user_interface.h"

#include "analog.h"
#include "rwflash.h"
#include "interrupt.h"
#include "json.h"
#include "httpd.h"
#include "client.h"

extern UartDevice UartDev;
extern char strConfigs[FLASH_CONFIGS_LEN];

/**
 * @brief UART receive buffer size
 */
#define RX_BUFF_SIZE 100

/**
 * @brief UART receive buffer array
 */
char uart_rx_buffer[RX_BUFF_SIZE];

/**
 * @brief UART receive counter
 */
uint8 uart_rx_cnt = 0;

/**
 * @brief Receive response send flag
 */
uint8 uart_rx_send = 0;

/**
 * @brief UART ADC variable
 */
uint16 vadc;

/**
 * @brief Deep-Sleep time-out
 */
uint64 vsleep=1000000; //1s

#define uart_recvTaskPrio        0
#define uart_recvTaskQueueLen    10
os_event_t    uart_recvTaskQueue[uart_recvTaskQueueLen];

#define DBG
#define DBG1 uart1_sendStr_no_wait
#define DBG2 os_printf

LOCAL void uart0_rx_intr_handler(void *para);

LOCAL void ICACHE_FLASH_ATTR
uart_config(uint8 uart_no)
{
    if (uart_no == UART1){
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_U1TXD_BK);
    }else{
        ETS_UART_INTR_ATTACH(uart0_rx_intr_handler,  &(UartDev.rcv_buff));
        PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0TXD_U);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_U0TXD);
    }
    uart_div_modify(uart_no, UART_CLK_FREQ / (UartDev.baut_rate));

    WRITE_PERI_REG(UART_CONF0(uart_no), ((UartDev.exist_parity & UART_PARITY_EN_M)  <<  UART_PARITY_EN_S)
                                                                        | ((UartDev.parity & UART_PARITY_M)  <<UART_PARITY_S )
                                                                        | ((UartDev.stop_bits & UART_STOP_BIT_NUM) << UART_STOP_BIT_NUM_S)
                                                                        | ((UartDev.data_bits & UART_BIT_NUM) << UART_BIT_NUM_S));

    SET_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);
    CLEAR_PERI_REG_MASK(UART_CONF0(uart_no), UART_RXFIFO_RST | UART_TXFIFO_RST);

    if (uart_no == UART0){
        WRITE_PERI_REG(UART_CONF1(uart_no),
        ((100 & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S) |
        (0x02 & UART_RX_TOUT_THRHD) << UART_RX_TOUT_THRHD_S |
        UART_RX_TOUT_EN|
        ((0x10 & UART_TXFIFO_EMPTY_THRHD)<<UART_TXFIFO_EMPTY_THRHD_S));//wjl
        SET_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_TOUT_INT_ENA |UART_FRM_ERR_INT_ENA);
    }else{
        WRITE_PERI_REG(UART_CONF1(uart_no),((UartDev.rcv_buff.TrigLvl & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S));//TrigLvl default val == 1
    }

    WRITE_PERI_REG(UART_INT_CLR(uart_no), 0xffff);
    SET_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_FULL_INT_ENA|UART_RXFIFO_OVF_INT_ENA);
}

 STATUS uart_tx_one_char(uint8 uart, uint8 TxChar)
{
    while (true){
        uint32 fifo_cnt = READ_PERI_REG(UART_STATUS(uart)) & (UART_TXFIFO_CNT<<UART_TXFIFO_CNT_S);
        if ((fifo_cnt >> UART_TXFIFO_CNT_S & UART_TXFIFO_CNT) < 126) {
            break;
        }
    }
    WRITE_PERI_REG(UART_FIFO(uart) , TxChar);
    return OK;
}

LOCAL void ICACHE_FLASH_ATTR
uart1_write_char(char c)
{
    if (c == '\n'){
        uart_tx_one_char(UART1, '\r');
        uart_tx_one_char(UART1, '\n');
    }else if (c == '\r'){

    }else{
        uart_tx_one_char(UART1, c);
    }
}

LOCAL void ICACHE_FLASH_ATTR
uart0_write_char_no_wait(char c)
{
    if (c == '\n'){
        uart_tx_one_char_no_wait(UART0, '\r');
        uart_tx_one_char_no_wait(UART0, '\n');
    }else if (c == '\r'){

    }
    else{
        uart_tx_one_char_no_wait(UART0, c);
    }

}

void ICACHE_FLASH_ATTR
uart0_tx_buffer(uint8 *buf, uint16 len)
{
    uint16 i;
    for (i = 0; i < len; i++)
    {
        uart_tx_one_char(UART0, buf[i]);
    }
}

/**
 * @brief UART0 send string
 * @param[in] String to send
 */
void ICACHE_FLASH_ATTR
uart0_sendStr(const char *str)
{
    while(*str){
        uart_tx_one_char(UART0, *str++);
    }
}
void at_port_print(const char *str) __attribute__((alias("uart0_sendStr")));

LOCAL void
uart0_rx_intr_handler(void *para)
{
    uint8 uart_no = UART0;
    uint8 fifo_len = 0;
    uint8 buf_idx = 0;
    uint8 temp,cnt;

    if(UART_FRM_ERR_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_FRM_ERR_INT_ST)){
        DBG1("FRM_ERR\r\n");
        WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_FRM_ERR_INT_CLR);
    }else if(UART_RXFIFO_FULL_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_FULL_INT_ST)){
        DBG("f");
        uart_rx_intr_disable(UART0);
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_FULL_INT_CLR);
        system_os_post(uart_recvTaskPrio, 0, 0);
    }else if(UART_RXFIFO_TOUT_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_TOUT_INT_ST)){
        DBG("t");
        uart_rx_intr_disable(UART0);
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_TOUT_INT_CLR);
        system_os_post(uart_recvTaskPrio, 0, 0);
    }else if(UART_TXFIFO_EMPTY_INT_ST == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_TXFIFO_EMPTY_INT_ST)){
        DBG("e");

        CLEAR_PERI_REG_MASK(UART_INT_ENA(UART0), UART_TXFIFO_EMPTY_INT_ENA);

        WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_TXFIFO_EMPTY_INT_CLR);

    }else if(UART_RXFIFO_OVF_INT_ST  == (READ_PERI_REG(UART_INT_ST(uart_no)) & UART_RXFIFO_OVF_INT_ST)){
        WRITE_PERI_REG(UART_INT_CLR(uart_no), UART_RXFIFO_OVF_INT_CLR);
        DBG1("RX OVF!!\r\n");
    }
}

/**
 * @brief UART config parse
 * @details Split String by "/"
 * @param[in] String Input
 * @param[out] Desired part string output
 * @param[in] Position of desired string
 */
LOCAL void ICACHE_FLASH_ATTR uart_conf_parse(char *strIN, char *strOUT, uint8 num){
    char strInput[90];
    char strSplit[3][30];
    uint8 i,j,cnt;

    os_strcpy(strInput,strIN);
    j=0; cnt=0;
    for(i=0;i<=os_strlen(strInput);i++){
        if(strInput[i]==' ' || strInput[i]=='\0'){
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

/**
 * @brief UART response callback
 * @details Callback Function not called directly
 * @param[in] Character from receive buffer
 */
LOCAL void ICACHE_FLASH_ATTR
uart_response(uint8 inChar){
    uint8 i;
    uint8 bootmode;
    char strReq[32];
    char user_id[FLASH_STRING_BUFF];
    char devs_id[FLASH_STRING_BUFF];
    char ip_numb[8];
    char url_req[16];
    char json_resp[JSON_RESP_LEN];

    const char cmdlist[]= "commands: "\
            "test "\
            "sdk "\
            "chip "\
            "when "\
            "fcpu "\
            "mems "\
            "adc "\
            "sleep "\
            "devsid "\
            "jsoninfo "\
            "restart "\
            "switch "\
            "sysinfo "\
            "apitest "\
            "apivalue "\
            "help";

    const char json_hdr_tes[] =
            "Content-Type: application/json\r\n";

    const char json_body_tes[] =
            "{\n"\
            "\"testMessage\": \"connection\"\n" \
            "}\n";

    char json_str_token[] = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjVlMWU5NmU3ZDMwNGZlNTQ3OTI4NjcwYyIsInJvbGUiOiJyZXNpZGVudCIsImlhdCI6MTU4MzkxMjQ2MywiZXhwIjoxNTgzOTk4ODYzfQ.B6WSr85owE11yrOJepBX19hYqLlCQP5jGl3BJvYe1-w";

    char json_hdr_value[512];
    os_sprintf(json_hdr_value,
               "Content-Type: application/x-www-form-urlencoded\r\n" \
               "x-access-token: %s\r\n"
               ,json_str_token);

    if(inChar == '\n' || inChar == '\r'){

        // Here are request string responses
        if(uart_rx_send == 0){
            uart0_sendStr("\r\n");

            uart_conf_parse(uart_rx_buffer,strReq,0);

            if(os_strcmp(strReq,"test")==0){
                uart0_sendStr("What to test?\r\n");
            }
            else if(os_strcmp(strReq,"sdk")==0){
                os_printf("[INFO] SDK: %s\r\n", system_get_sdk_version());
            }
            else if(os_strcmp(strReq,"chip")==0){
                os_printf("[INFO] Chip ID: %08X\r\n", system_get_chip_id());
            }
            else if(os_strcmp(strReq,"when")==0){
                os_printf("[INFO] Compiled at %s %s\r\n", __DATE__,__TIME__);
            }
            else if(os_strcmp(strReq,"fcpu")==0){
                os_printf("[INFO] CPU Freq: %d MHz\r\n", system_get_cpu_freq());
            }
            else if(os_strcmp(strReq,"mems")==0){
                os_printf("[INFO] Memory Info:\r\n"); system_print_meminfo();
            }
            else if(os_strcmp(strReq,"adc")==0){
                vadc = user_get_adc();
                os_printf("[INFO] ADC Input: %4d\r\n",vadc);
            }
            else if(os_strcmp(strReq,"sleep")==0){
                os_printf("[INFO] Entering Deep Sleep\r\n");
                system_deep_sleep_set_option(0);
                system_deep_sleep(10*vsleep); // 10s
            }
            else if(os_strcmp(strReq,"devsid")==0){
                uart_conf_parse(uart_rx_buffer,devs_id,1);

                if(os_strcmp(devs_id,"")==0){
                    os_printf("usage: devsid <10-chars unique permutation>\r\n");
                }
                else{
                    os_printf("[INFO] new deviceid: %s\r\n",devs_id);

                    os_memset(strConfigs,0,FLASH_CONFIGS_LEN);
                    rwflash_str_read(CONFIGS_FLASH_ADDR,strConfigs);
                    os_printf("String Config get: %s\r\n",strConfigs);
                    rwflash_conf_parse(strConfigs,user_id,FLASH_USERID);

                    os_sprintf(strConfigs,"/%s/%s",user_id,devs_id);
                    os_printf("String Config set: %s\r\n",strConfigs);
                    rwflash_str_write(CONFIGS_FLASH_ADDR,strConfigs);
                }
            }
            else if(os_strcmp(strReq,"jsoninfo")==0){
                os_printf("Building JSON info \r\n");
                json_infoall(json_resp);
                os_printf("JSON Data: %s\r\n",json_resp);
            }
            else if(os_strcmp("restart",strReq)==0){
                for(i=0;i<100;i++){os_delay_us(10000);}
                system_restart();
            }
            else if(os_strcmp("switch",strReq)==0){
                for(i=0;i<100;i++){os_delay_us(10000);}
                user_wifi_switch();
            }
            else if(os_strcmp("sysinfo",strReq)==0){
                os_printf("\r\n\r\n[INFO] -------------------------------------------\r\n");

                os_printf("[INFO] Compiled at %s %s\r\n", __DATE__,__TIME__);
                os_printf("[INFO] SDK: %s\r\n", system_get_sdk_version());
                os_printf("[INFO] Chip ID: %08X\r\n", system_get_chip_id());
                os_printf("[INFO] BOOT Version: %d\r\n",system_get_boot_version());
                os_printf("[INFO] BIN User addr: 0x%08X\r\n",system_get_userbin_addr());

                bootmode = system_get_boot_mode();
                if(bootmode == 0){ os_printf("[INFO] Boot using Enhance Mode\r\n"); }
                else{os_printf("[INFO] Boot using Normal Mode\r\n");}

                os_printf("[INFO] CPU Freq: %d MHz\r\n", system_get_cpu_freq());
                os_printf("[INFO] Memory Info:\r\n"); system_print_meminfo();

                os_printf("[INFO] -------------------------------------------\r\n");
                os_printf("\r\n\r\n");
            }
            else if(os_strcmp("request",strReq)==0){
                uart_conf_parse(uart_rx_buffer,ip_numb,1);
                os_sprintf(url_req,"http://192.168.4.%s:8000/",ip_numb);
                os_printf("HTTP request to %s\r\n",url_req);
                tcp_client_get(url_req);
            }
            else if(os_strcmp("reqagent",strReq)==0){
                uart_conf_parse(uart_rx_buffer,ip_numb,1);
                os_sprintf(url_req,"http://192.168.4.%s:8000/agen",ip_numb);
                os_printf("HTTP request to %s\r\n",url_req);
                tcp_client_get(url_req);
            }
            else if(os_strcmp("apitest",strReq)==0){
                os_sprintf(url_req,"http://safevision.id:6500/sensor/test");
                os_printf("HTTP request to %s\r\n",url_req);
                tcp_client_post(url_req,json_body_tes,json_hdr_tes);
            }
            else if(os_strcmp("apivalue",strReq)==0){
                os_sprintf(url_req,"http://safevision.id:6500/sensor/setById/SNS00107892945/0");
                os_printf("HTTP request to %s\r\n",url_req);
                tcp_client_gethdr(url_req,json_hdr_value);
            }
            else if(os_strcmp("help",strReq)==0){
                os_printf("%s\r\n",cmdlist);
            }
            else{
                os_strcat(strReq,"\r\n");
                uart0_sendStr("Serial Data is ");
                uart0_sendStr(strReq);
            }

            os_memset(uart_rx_buffer,0,sizeof(uart_rx_buffer));
            uart_rx_cnt = 0;
            uart_rx_send = 1;
        }
    }
    else{
        uart_rx_buffer[uart_rx_cnt] = inChar;
        uart_rx_cnt++;
        uart_rx_send = 0;
    }
}

LOCAL void ICACHE_FLASH_ATTR ///////
uart_recvTask(os_event_t *events)
{
    if(events->sig == 0){
        uint8 fifo_len = (READ_PERI_REG(UART_STATUS(UART0))>>UART_RXFIFO_CNT_S)&UART_RXFIFO_CNT;
        uint8 d_tmp = 0;
        uint8 idx=0;
        for(idx=0;idx<fifo_len;idx++) {
            d_tmp = READ_PERI_REG(UART_FIFO(UART0)) & 0xFF;

            if(d_tmp == '\r' || d_tmp == '\n'){}
            else{ uart_tx_one_char(UART0, d_tmp); }

            uart_response(d_tmp);
        }
        WRITE_PERI_REG(UART_INT_CLR(UART0), UART_RXFIFO_FULL_INT_CLR|UART_RXFIFO_TOUT_INT_CLR);
        uart_rx_intr_enable(UART0);
    }
}

/**
 * @brief UART response callback
 * @param[in] Baudrate value for UART0
 * @param[in] Baudrate value for UART1
 */
void ICACHE_FLASH_ATTR
uart_init(UartBautRate uart0_br, UartBautRate uart1_br)
{
    system_os_task(uart_recvTask, uart_recvTaskPrio, uart_recvTaskQueue, uart_recvTaskQueueLen);

    UartDev.baut_rate = uart0_br;
    uart_config(UART0);
    UartDev.baut_rate = uart1_br;
    uart_config(UART1);
    ETS_UART_INTR_ENABLE();
}

void ICACHE_FLASH_ATTR
uart_reattach()
{
    uart_init(BIT_RATE_115200, BIT_RATE_115200);
}

STATUS uart_tx_one_char_no_wait(uint8 uart, uint8 TxChar)
{
    uint8 fifo_cnt = (( READ_PERI_REG(UART_STATUS(uart))>>UART_TXFIFO_CNT_S)& UART_TXFIFO_CNT);
    if (fifo_cnt < 126) {
        WRITE_PERI_REG(UART_FIFO(uart) , TxChar);
    }
    return OK;
}

STATUS uart0_tx_one_char_no_wait(uint8 TxChar)
{
    uint8 fifo_cnt = (( READ_PERI_REG(UART_STATUS(UART0))>>UART_TXFIFO_CNT_S)& UART_TXFIFO_CNT);
    if (fifo_cnt < 126) {
        WRITE_PERI_REG(UART_FIFO(UART0) , TxChar);
    }
    return OK;
}

void uart1_sendStr_no_wait(const char *str)
{
    while(*str){
        uart_tx_one_char_no_wait(UART1, *str++);
    }
}

void uart_rx_intr_disable(uint8 uart_no)
{
    CLEAR_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_FULL_INT_ENA|UART_RXFIFO_TOUT_INT_ENA);
}

void uart_rx_intr_enable(uint8 uart_no)
{
    SET_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_FULL_INT_ENA|UART_RXFIFO_TOUT_INT_ENA);
}
/** @} */
