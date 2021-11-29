#ifndef MY_FUZZY_H
#define MY_FUZZY_H

#define RULE_SIZE 9

/********************************************/
/* Definisi Fuzzyfikasi Hasil               */
/********************************************/

#define OUT_BIASA 0

#define OUT_AWAS  1

#define OUT_JATUH 2

class MyFuzzy{

    public:
        MyFuzzy();

        void Accel(float input_accel);
        void Mic(unsigned int input_mic);
        unsigned int Evaluasi(void);
        unsigned int Decision(unsigned int index);

        float f_accel[3];
        float f_mic[3];

        float f_rule[RULE_SIZE];

        //variabel fuzzy untuk accel
        double vf_accel_rendah[2] = {7, 14};
        double vf_accel_sedang[3] = {13, 14, 15};
        double vf_accel_tinggi[2] = {14, 16};

        //variabel fuzzy untuk mic
        unsigned int vf_mic_rendah[2] = {250, 350};
        unsigned int vf_mic_sedang[3] = {300, 350, 450};
        unsigned int vf_mic_tinggi[2] = {350, 500};

};

#endif // MY_FUZZY_H
