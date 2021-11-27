
#include "ch.h"
#include "hal.h"

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config =
{
  {VAL_GPIOAODR, VAL_GPIOACRL, VAL_GPIOACRH},
  {VAL_GPIOBODR, VAL_GPIOBCRL, VAL_GPIOBCRH},
  {VAL_GPIOCODR, VAL_GPIOCCRL, VAL_GPIOCCRH},
  {VAL_GPIODODR, VAL_GPIODCRL, VAL_GPIODCRH},
  {VAL_GPIOEODR, VAL_GPIOECRL, VAL_GPIOECRH},
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  stm32_clock_init();
}

#if HAL_USE_MMC_SPI
/* Board-related functions related to the MMC_SPI driver.*/
bool_t mmc_lld_is_card_inserted(MMCDriver *mmcp) {

  (void)mmcp;
  return palReadPad(GPIOC, GPIOC_MMCCP);
}

bool_t mmc_lld_is_write_protected(MMCDriver *mmcp) {

  (void)mmcp;
  return !palReadPad(GPIOC, GPIOC_MMCWP);
}
#endif

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
}
