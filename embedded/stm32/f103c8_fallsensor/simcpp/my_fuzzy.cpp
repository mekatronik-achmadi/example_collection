#include "my_fuzzy.h"

MyFuzzy::MyFuzzy() {
    //do nothing for now
}

void MyFuzzy::Accel(float input_accel){
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

void MyFuzzy::Mic(unsigned int input_mic){
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

unsigned int MyFuzzy::Decision(unsigned int index){
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

unsigned int MyFuzzy::Evaluasi(void){
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
