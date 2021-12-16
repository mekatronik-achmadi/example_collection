GFXINC  += ./disp/
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_CHIBIOS=TRUE

include $(GFXLIB)/drivers/gdisp/ILI9341/driver.mk
