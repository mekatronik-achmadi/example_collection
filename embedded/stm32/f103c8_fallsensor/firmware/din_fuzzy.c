/*
              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

 Copyright (C) 2018 Achmadi S.T.

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

/**
 * @file    din_fuzzy.c
 * @brief   Fuzzy Logic code.
 *
 * @addtogroup Fuzzy
 * @{
 */

#include "din_fuzzy.h"

/**
 * @brief   Accelerometer fuzzy array variable
 */
static float f_accel[3];

/**
 * @brief   Mic fuzzy array variable
 */
static float f_mic[3];

/**
 * @brief   Fuzzy rule array variable
 */
static float f_rule[RULE_SIZE];

/**
 * @brief   Accelerometer low membership array variable
 */
static float vf_accel_rendah[2] = {7, 7.78493};

/**
 * @brief   Accelerometer mid membership array variable
 */
static float vf_accel_sedang[3] = {7.6109, 9, 10.3521};

/**
 * @brief   Accelerometer high membership array variable
 */
static float vf_accel_tinggi[2] = {9.0384, 13};

/**
 * @brief   Mic low membership array variable
 */
static float vf_mic_rendah[2] = {5, 7.57378};

/**
 * @brief   Mic mid membership array variable
 */
static float vf_mic_sedang[3] = {5.5467, 8, 9.31291};

/**
 * @brief   Mic high membership array variable
 */
static float vf_mic_tinggi[2] = {7.33903,12 };

/**
 * @brief   Accelerometer membership fuzzyfication
 * @param[in] input_accel Input from Accelerometer
 */
static void Accel(float input_accel){
    // fuzzy RENDAH
    if(input_accel <= vf_accel_rendah[0]){
        f_accel[0] = 1;
    }
    else if((input_accel > vf_accel_rendah[0]) && (input_accel <= vf_accel_rendah[1])){
        f_accel[0] = (vf_accel_rendah[1] - input_accel)/(vf_accel_rendah[1] - vf_accel_rendah[0]);
    }
    else if(input_accel > vf_accel_rendah[1]){
        f_accel[0] = 0;
    }

    // fuzzy SEDANG
    if(input_accel <= vf_accel_sedang[0]){
        f_accel[1] = 0;
    }
    else if((input_accel > vf_accel_sedang[0]) && (input_accel <= vf_accel_sedang[1])){
        f_accel[1] = (input_accel - vf_accel_sedang[0])/(vf_accel_sedang[1] - vf_accel_sedang[0]);
    }
    else if((input_accel > vf_accel_sedang[1]) && (input_accel <= vf_accel_sedang[2])){
        f_accel[1] = (vf_accel_sedang[2] - input_accel)/(vf_accel_sedang[2] - vf_accel_sedang[1]);
    }
    else if(input_accel > vf_accel_sedang[2]){
        f_accel[1] = 0;
    }

    // fuzzy TINGGI
    if(input_accel <= vf_accel_tinggi[0]){
        f_accel[2] = 0;
    }
    else if((input_accel > vf_accel_tinggi[0]) && (input_accel <= vf_accel_tinggi[1])){
        f_accel[2] = (input_accel - vf_accel_tinggi[0])/(vf_accel_tinggi[1] - vf_accel_tinggi[0]);
    }
    else if(input_accel > vf_accel_tinggi[1]){
        f_accel[2] = 1;
    }
}

/**
 * @brief   Mic membership fuzzyfication
 * @param[in] input_mic Input from Mic
 */
static void Mic(unsigned int input_mic){
    // fuzzy RENDAH
    if(input_mic <= vf_mic_rendah[0]){
        f_mic[0] = 1;
    }
    else if((input_mic > vf_mic_rendah[0]) && (input_mic <= vf_mic_rendah[1])){
        f_mic[0] = (vf_mic_rendah[1] - input_mic)/(vf_mic_rendah[1] - vf_mic_rendah[0]);
    }
    else if(input_mic > vf_mic_rendah[1]){
        f_mic[0] = 0;
    }

    // fuzzy SEDANG
    if(input_mic <= vf_mic_sedang[0]){
        f_mic[1] = 0;
    }
    else if((input_mic > vf_mic_sedang[0]) && (input_mic <= vf_mic_sedang[1])){
        f_mic[1] = (input_mic - vf_mic_sedang[0])/(vf_mic_sedang[1] - vf_mic_sedang[0]);
    }
    else if((input_mic > vf_mic_sedang[1]) && (input_mic <= vf_mic_sedang[2])){
        f_mic[1] = (vf_mic_sedang[2] - input_mic)/(vf_mic_sedang[2] - vf_mic_sedang[1]);
    }
    else if(input_mic > vf_mic_sedang[2]){
        f_mic[1] = 0;
    }

    // fuzzy TINGGI
    if(input_mic <= vf_mic_tinggi[0]){
        f_mic[2] = 0;
    }
    else if((input_mic > vf_mic_tinggi[0]) && (input_mic <= vf_mic_tinggi[1])){
        f_mic[2] = (input_mic - vf_mic_tinggi[0])/(vf_mic_tinggi[1] - vf_mic_tinggi[0]);
    }
    else if(input_mic > vf_mic_tinggi[1]){
        f_mic[2] = 1;
    }
}

/**
 * @brief   Evaluasi Fuzzy
 * @return Index maximum membership of fuzzy array
 */
static u_int16_t Evaluasi(void){
    unsigned int m,n;
    unsigned int i,idx=0;
    float v_max;

    for(m=0;m<=2;m++){
        for(n=0;n<=2;n++){
            f_rule[3*m + n]=f_accel[m]*f_mic[n];
        }
    }

    v_max = f_rule[0];

    for(i=1;i<RULE_SIZE;i++){
        if(f_rule[i] > v_max){
            v_max = f_rule[i];
            idx = i;
        }
    }

    return idx;
}

/**
 * @brief  Decision based on fuzzy rule array
 * @return Index of Response fuzzy logic
 */
static u_int16_t Decision(unsigned int index){
    unsigned int out_fuzzy=0;

    switch (index){
    case 0:
        out_fuzzy = OUT_BIASA; //rendah,sunyi
        break;
    case 1:
        out_fuzzy = OUT_BIASA; //rendah,lumayan
        break;
    case 2:
        out_fuzzy = OUT_BIASA; //rendah,ramai
        break;
    case 3:
        out_fuzzy = OUT_BIASA; //sedang,sunyi
        break;
    case 4:
        out_fuzzy = OUT_AWAS; //sedang,lumayan
        break;
    case 5:
        out_fuzzy = OUT_AWAS; //sedang,ramai
        break;
    case 6:
        out_fuzzy = OUT_AWAS; //tinggi,sunyi
        break;
    case 7:
        out_fuzzy = OUT_AWAS; //tinggi,lumayan
        break;
    case 8:
        out_fuzzy = OUT_JATUH; //tinggi,ramai
        break;
    }

    return out_fuzzy;
}

/**
 * @brief  Main Fuzzy routine
 * @return Response fuzzy logic
 */
u_int8_t d_fuzzy(float vmag, float vmic){
    Accel(vmag);
    Mic(vmic);

    return Decision(Evaluasi());
}
/** @} */
