#include <iostream>
#include "my_fuzzy.h"

using namespace std;

unsigned int i;

float accel_var;
unsigned int sensorValue;

unsigned int hasilfuzzy;
float hasilfuzzy_frule;

MyFuzzy fuzz;

int main(int argc, char *argv[])
{
    //argumen termasuk nama app sendiri (array 0)
    if(argc!=3){
        printf("jumlah argumen tidak sesuai\r\n");
        return 1;
    }

    accel_var = atof(argv[1]);
    sensorValue = atoi(argv[2]);

    fuzz.Accel(accel_var);
    fuzz.Mic(sensorValue);
    hasilfuzzy_frule = fuzz.f_rule[fuzz.Evaluasi()];
    hasilfuzzy = fuzz.Decision(fuzz.Evaluasi());

    printf("nilai accel= %5.2f\r\n",accel_var);
    printf("nilai mic  = %4i\r\n",sensorValue);

    printf("nilai frule= %5.2f\r\n",hasilfuzzy_frule);
    printf("nilai akhir= %4i\r\n",hasilfuzzy);


    switch(hasilfuzzy){
        case OUT_BIASA: printf("status: BIASA\r\n"); break;
        case OUT_AWAS: printf("status: AWAS\r\n"); break;
        case OUT_JATUH: printf("status: JATUH\r\n"); break;
    }

    return 0;
}
