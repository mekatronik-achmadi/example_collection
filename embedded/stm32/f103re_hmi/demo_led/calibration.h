#ifndef _CALIBRATION_H
#define _CALIBRATION_H

#include <string.h>
#include "gfx.h"

// Calibration data
float calibrationData[] = {
	1,		// ax
	1,		// bx
	0,		// cy
	1,		// ay
	1,		// by
	0 		// cy
};

// The loading routine
bool_t LoadMouseCalibration(unsigned instance, void *data, size_t sz)
{
	(void)instance;
	
	if (sz != sizeof(calibrationData)) {
		return FALSE;
	}
	
	memcpy(data, (void*)&calibrationData, sz);
	
	return TRUE;
}

#endif /* _CALIBRATION_H */

