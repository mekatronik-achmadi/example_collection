GFXINC	+= ./ugfx/
GFXSRC	+=
GFXDEFS += -DGFX_USE_CHIBIOS=TRUE

include $(GFXLIB)/drivers/gdisp/ILI9320/driver.mk

include $(GFXLIB)/drivers/ginput/touch/ADS7843/driver.mk

