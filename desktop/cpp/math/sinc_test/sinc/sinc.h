/**
 * @file sinc.h
 * @brief Sines Calculation header
 *
 * @addtogroup SINC
 * @{
 */

#ifndef _SINC_H_
#define _SINC_H_

#ifndef DEFAULT_N
 #define DEFAULT_N   1000
#endif

/**
 * @brief Sines Calculation
 * @details Apply numerical calculation of sin(pi*x)/(pi*x) using infinite product form.
 * @param x Real Number as Sin function input.
 * @param n Recursion iteration number. Don't to big as it might consume memory a lot.
 * @return Sines estimation
 */
double sinCalc(double x, unsigned int n);

#endif

/**  @} */


