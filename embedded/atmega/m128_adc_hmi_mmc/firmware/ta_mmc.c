#include "ta_mmc.h"

char mmc_str[MMC_STR_LONG];
extern uint8_t cobavar;

FATFS FatFs;
FIL Fil;
UINT bw;

void ta_mmc_WriteTest(void){

	sprintf(mmc_str,"coba= %4i \r\n",cobavar);

    f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */

    if (f_open(&Fil, "newfile.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_READ) == FR_OK) {	/* Create a file */
	
		f_lseek(&Fil, f_size(&Fil));
        
		f_write(&Fil, mmc_str, strlen(mmc_str), &bw);	/* Write data to the file */

        f_close(&Fil);								/* Close the file */
    }
	
	f_mount(0, "", 0); 
}
