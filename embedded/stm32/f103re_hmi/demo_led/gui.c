/******************************************************************************/
/* This file has been generated by the uGFX-Studio                            */
/*                                                                            */
/* http://ugfx.org                                                            */
/******************************************************************************/

#include "calibration.h"
#include "colors.h"
#include "widgetstyles.h"
#include "gui.h"

// GListeners
GListener glistener;

// GHandles
GHandle ghContainerPage0;
GHandle ghImagebox1;

// Fonts
font_t dejavu_sans_16;

// Images

static void createPagePage0(void)
{
	GWidgetInit wi;
	gwinWidgetClearInit(&wi);


	// create container widget: ghContainerPage0
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = 240;
	wi.g.height = 320;
	wi.g.parent = 0;
	wi.text = "Container";
	wi.customDraw = 0;
	wi.customParam = 0;
	wi.customStyle = 0;
	ghContainerPage0 = gwinContainerCreate(0, &wi, 0);

	// create button widget: ghImagebox1
	wi.g.show = TRUE;
	wi.g.x = 30;
	wi.g.y = 20;
	wi.g.width = 176;
	wi.g.height = 280;
	wi.g.parent = ghContainerPage0;
	ghImagebox1 = gwinImageCreate(0, &wi.g);
	gwinImageOpenFile(ghImagebox1, "rsc/logo.bmp");
}

void guiShowPage(unsigned pageIndex)
{
	// Hide all pages
	gwinHide(ghContainerPage0);

	// Show page selected page
	switch (pageIndex) {
	case 0:
		gwinShow(ghContainerPage0);
		break;

	default:
		break;
	}
}

void guiCreate(void)
{
	GWidgetInit wi;

	// Prepare fonts
	dejavu_sans_16 = gdispOpenFont("DejaVuSans16");

	// Prepare images

	// GWIN settings
	gwinWidgetClearInit(&wi);
	gwinSetDefaultFont(dejavu_sans_16);
	gwinSetDefaultStyle(&black, FALSE);
	gwinSetDefaultColor(black_studio);
	gwinSetDefaultBgColor(white_studio);

	// Create all the display pages
	createPagePage0();

	// Select the default display page
	guiShowPage(0);

}

void guiEventLoop(void)
{
	GEvent* pe;

	while (1) {
		// Get an event
		pe = geventEventWait(&glistener, 0);
		switch (pe->type) {
		}

	}
}
