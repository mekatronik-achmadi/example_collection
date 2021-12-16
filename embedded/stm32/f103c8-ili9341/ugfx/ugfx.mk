GFXINC	+= ./ugfx/
GFXSRC	+=
GFXDEFS += -DGFX_USE_CHIBIOS=TRUE

include $(GFXLIB)/drivers/gdisp/ILI9341/driver.mk

