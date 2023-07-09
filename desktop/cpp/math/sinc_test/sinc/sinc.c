/**
 * @file sinc.c
 * @brief Sines Calculation code
 *
 * @addtogroup SINC
 * @{
 */

#include <math.h>
#include "sinc.h"

double sinCalc(double x, unsigned int n){
    return (n==0) ? 1 :
        (1.0 - (x*x) / (n*n)) * sinCalc(x,n-1);
}

/**  @} */


