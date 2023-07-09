/**
 * @file main.c
 * @brief Desktop Main code
 *
 * @addtogroup MAIN
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sinc.h"

int main(int argc, char *argv[])
{

    if(argc != 3) {
        printf("using default value\n");
        double defX = 0.5;
        unsigned int defN = DEFAULT_N;

        printf("SinC of X = %f and N = %i is %f\n",
                defX,
                defN,
                sinCalc(defX, defN));
    }
    else{
        double valX = atof(argv[1]);
        unsigned valN = atoi(argv[2]);

        printf("SinC of X = %f and N = %i is %f\n",
                valX,
                valN,
                sinCalc(valX, valN));
    }

    return 0;
}

/**  @} */


