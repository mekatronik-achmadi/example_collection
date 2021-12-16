#include "m8.h"

extern u_int8_t val_EFUSE;
extern u_int8_t val_HFUSE;
extern u_int8_t val_LFUSE;

m8::m8()
{

}

u_int8_t m8::fuse_default(u_int8_t fuse_part){
    u_int8_t result=0x00;

    if(fuse_part==LFUSE){
        result = 0xE4;
    }
    else if(fuse_part==HFUSE){
        result = 0xD9;
    }
    else if(fuse_part==EFUSE){
        result = 0xFF;
    }

    return result;
}

u_int8_t m8::fuse_restrict(u_int8_t fuse_part){
    u_int8_t result=0x00;

    if(fuse_part==LFUSE){
        result = 0x00;
    }
    else if(fuse_part==HFUSE){
        sH(result,5);
        sH(result,7);
    }
    else if(fuse_part==EFUSE){
        result = 0xFF;
    }

    return result;
}

QStringList m8::fuse_string(u_int8_t fuse_part){
    QStringList result;

    if(fuse_part==LFUSE){
        result << "CKSEL0";
        result << "CKSEL1";
        result << "CKSEL2";
        result << "CKSEL3";
        result << "SUT0";
        result << "SUT1";
        result << "BODEN";
        result << "BODLEVEL";
    }
    else if(fuse_part==HFUSE){
        result << "BOOTRST";
        result << "BOOTSZ0";
        result << "BOOTSZ1";
        result << "EESAVE";
        result << "CKOPT";
        result << "SPIEN";
        result << "WDTON";
        result << "RSTDISBL";
    }
    else if(fuse_part==EFUSE){
        u_int8_t i;
        for(i=0;i<8;i++){
            result << "UNUSED";
        }
    }

    return result;
}

QStringList m8::fuse_tooltip(u_int8_t fuse_part){
    QStringList result;

    if(fuse_part==LFUSE){
        result << "Clock Selection";
        result << "Clock Selection";
        result << "Clock Selection";
        result << "Clock Selection";
        result << "Start Up Time";
        result << "Start Up Time";
        result << "Enable Brown-Out Detection";
        result << "Brown-Out Detection Voltage Level";
    }
    else if(fuse_part==HFUSE){
        result << "Boot Reset Vector $0000 enable";
        result << "Boot Size";
        result << "Boot Size";
        result << "EEPROM Save during Chip Erase";
        result << "Clock/Oscillator Options";
        result << "SPI Programming enable";
        result << "Watchdog always on";
        result << "Disable Reset and use as I/O pin";
    }
    else if(fuse_part==EFUSE){
        u_int8_t i;
        for(i=0;i<8;i++){
            result << "UNUSED";
        }
    }

    return result;
}

QStringList m8::bod_string(){
    QStringList result;

    result << "disable";
    result << "2.6v";
    result << "4.0v";

    return result;
}

u_int8_t m8::bod_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index){

    u_int8_t result;
    result = ~fuse_input;

    if(fuse_part == LFUSE){
        if(menu_index==0){
            sL(result,6);
            sL(result,7);
        }
        else if(menu_index==1){
            sH(result,6);
            sL(result,7);
        }
        else if(menu_index==2){
            sH(result,6);
            sH(result,7);
        }
    }

    result = ~result;
    return result;

}

u_int8_t m8::bod_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    (void) hfuse_input;
    (void) efuse_input;

    u_int8_t result = 0;
    lfuse_input = ~lfuse_input;

    u_int8_t v_reg;
    bool boden = iH(lfuse_input,6);
    bool bodlevel = iH(lfuse_input,7);
    v_reg = ( boden << 0 ) | (bodlevel << 1);

    if(v_reg == 0b00){
        result = 0;
    }
    else if(v_reg == 0b01){
        result = 1;
    }
    else if(v_reg == 0b11){
        result = 2;
    }

    return result;
}

QStringList m8::bootsz_string(){
    QStringList result;

    result << "128 at $0F80";
    result << "256 at $0F00";
    result << "512 at $0E00";
    result << "1024 at $0C00";

    return result;
}

u_int8_t m8::bootsz_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index){

    u_int8_t result;
    result = ~fuse_input;

    if(fuse_part == HFUSE){
        if(menu_index==0){
            sL(result,1);
            sL(result,2);
        }
        else if(menu_index==1){
            sH(result,1);
            sL(result,2);
        }
        else if(menu_index==2){
            sL(result,1);
            sH(result,2);
        }
        else if(menu_index==3){
            sH(result,1);
            sH(result,2);
        }
    }

    result = ~result;
    return result;

}

u_int8_t m8::bootsz_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    (void) lfuse_input;
    (void) efuse_input;

    u_int8_t result =0;
    hfuse_input = ~hfuse_input;

    u_int8_t v_reg;
    bool bootsz0 = iH(hfuse_input,1);
    bool bootsz1 = iH(hfuse_input,2);
    v_reg = (bootsz0 << 0) | (bootsz1 << 1);

    if( v_reg == 0b00 ){
        result =0;
    }
    else if( v_reg == 0b01 ){
        result =1;
    }
    else if( v_reg == 0b010 ){
        result =2;
    }
    else if( v_reg == 0b11 ){
        result =3;
    }

    return result;
}

QStringList m8::osc_string(){
    QStringList result;

    result << "Int RC 1MHz; Start-Up BOD";  //011 1110 0
    result << "Int RC 1MHz; Start-Up Fast"; //010 1110 1
    result << "Int RC 1MHz; Start-Up Slow"; //001 1110 2

    result << "Int RC 2MHz; Start-Up BOD";  //011 1101 3
    result << "Int RC 2MHz; Start-Up Fast"; //010 1101 4
    result << "Int RC 2MHz; Start-Up Slow"; //001 1101 5

    result << "Int RC 4MHz; Start-Up BOD";  //011 1100 6
    result << "Int RC 4MHz; Start-Up Fast"; //010 1100 7
    result << "Int RC 4MHz; Start-Up Slow"; //001 1100 8

    result << "Int RC 8MHz; Start-Up BOD";  //011 1011 9
    result << "Int RC 8MHz; Start-Up Fast"; //010 1011 10
    result << "Int RC 8MHz; Start-Up Slow"; //001 1011 11

    result << "Ext RC 0.1-0.9 MHz; Start-Up BOD";  //011 1010 12
    result << "Ext RC 0.1-0.9 MHz; Start-Up Fast"; //010 1010 13
    result << "Ext RC 0.1-0.9 MHz; Start-Up Slow"; //001 1010 14

    result << "Ext RC 0.9-3.0 MHz; Start-Up BOD";  //011 1001 15
    result << "Ext RC 0.9-3.0 MHz; Start-Up Fast"; //010 1001 16
    result << "Ext RC 0.9-3.0 MHz; Start-Up Slow"; //001 1001 17

    result << "Ext RC 3.0-8.0 MHz; Start-Up BOD";  //011 1000 18
    result << "Ext RC 3.0-8.0 MHz; Start-Up Fast"; //010 1000 19
    result << "Ext RC 3.0-8.0 MHz; Start-Up Slow"; //001 1000 20

    result << "Ext RC 8.0-12.0 MHz; Start-Up BOD";  //011 0100 21
    result << "Ext RC 8.0-12.0 MHz; Start-Up Fast"; //010 0100 22
    result << "Ext RC 8.0-12.0 MHz; Start-Up Slow"; //001 0100 23

    result << "Ext Xtall Low; Start-Up BOD";  //111 0110 24
    result << "Ext Xtall Low; Start-Up Fast"; //110 0110 25
    result << "Ext Xtall Low; Start-Up Slow"; //101 0110 26

    result << "Ext Xtall Mid; Start-Up BOD";  //110 0010 27
    result << "Ext Xtall Mid; Start-Up Fast"; //101 0010 28
    result << "Ext Xtall Mid; Start-Up Slow"; //100 0010 29

    result << "Ext Xtall Hi; Start-Up BOD";  //110 0000 30
    result << "Ext Xtall Hi; Start-Up Fast"; //101 0000 31
    result << "Ext Xtall Hi; Start-Up Slow"; //100 0000 32

    result << "UNUSED";

    return result;
}

u_int8_t m8::osc_get(u_int8_t fuse_part, u_int8_t fuse_input, int8_t menu_index){

    u_int8_t result;
    result = ~fuse_input;

    if(fuse_part == LFUSE){
        if(menu_index==0){
            sH(result,5);sH(result,4);
            sH(result,3);sH(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==1){
            sH(result,5);sL(result,4);
            sH(result,3);sH(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==2){
            sL(result,5);sH(result,4);
            sH(result,3);sH(result,2);sH(result,1);sL(result,0);
        }


        else if(menu_index==3){
            sH(result,5);sH(result,4);
            sH(result,3);sH(result,2);sL(result,1);sH(result,0);
        }
        else if(menu_index==4){
            sH(result,5);sL(result,4);
            sH(result,3);sH(result,2);sL(result,1);sH(result,0);
        }
        else if(menu_index==5){
            sL(result,5);sH(result,4);
            sH(result,3);sH(result,2);sL(result,1);sH(result,0);
        }


        else if(menu_index==6){
            sH(result,5);sH(result,4);
            sH(result,3);sH(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==7){
            sH(result,5);sL(result,4);
            sH(result,3);sH(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==8){
            sL(result,5);sH(result,4);
            sH(result,3);sH(result,2);sL(result,1);sL(result,0);
        }


        else if(menu_index==9){
            sH(result,5);sH(result,4);
            sH(result,3);sL(result,2);sH(result,1);sH(result,0);
        }
        else if(menu_index==10){
            sH(result,5);sL(result,4);
            sH(result,3);sL(result,2);sH(result,1);sH(result,0);
        }
        else if(menu_index==11){
            sL(result,5);sH(result,4);
            sH(result,3);sL(result,2);sH(result,1);sH(result,0);
        }


        else if(menu_index==12){
            sH(result,5);sH(result,4);
            sH(result,3);sL(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==13){
            sH(result,5);sL(result,4);
            sH(result,3);sL(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==14){
            sL(result,5);sH(result,4);
            sH(result,3);sL(result,2);sH(result,1);sL(result,0);
        }


        else if(menu_index==15){
            sH(result,5);sH(result,4);
            sH(result,3);sL(result,2);sL(result,1);sH(result,0);
        }
        else if(menu_index==16){
            sH(result,5);sL(result,4);
            sH(result,3);sL(result,2);sL(result,1);sH(result,0);
        }
        else if(menu_index==17){
            sL(result,5);sH(result,4);
            sH(result,3);sL(result,2);sL(result,1);sH(result,0);
        }


        else if(menu_index==18){
            sH(result,5);sH(result,4);
            sH(result,3);sL(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==19){
            sH(result,5);sL(result,4);
            sH(result,3);sL(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==20){
            sL(result,5);sH(result,4);
            sH(result,3);sL(result,2);sL(result,1);sL(result,0);
        }


        else if(menu_index==21){
            sH(result,5);sH(result,4);
            sL(result,3);sH(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==22){
            sH(result,5);sL(result,4);
            sL(result,3);sH(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==23){
            sL(result,5);sH(result,4);
            sL(result,3);sH(result,2);sL(result,1);sL(result,0);
        }


        else if(menu_index==24){
            sH(result,5);sH(result,4);
            sL(result,3);sH(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==25){
            sH(result,5);sL(result,4);
            sL(result,3);sH(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==26){
            sL(result,5);sH(result,4);
            sL(result,3);sH(result,2);sH(result,1);sL(result,0);
        }


        else if(menu_index==27){
            sH(result,5);sL(result,4);
            sL(result,3);sL(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==28){
            sL(result,5);sH(result,4);
            sL(result,3);sL(result,2);sH(result,1);sL(result,0);
        }
        else if(menu_index==29){
            sL(result,5);sL(result,4);
            sL(result,3);sL(result,2);sH(result,1);sL(result,0);
        }


        else if(menu_index==30){
            sH(result,5);sL(result,4);
            sL(result,3);sL(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==31){
            sL(result,5);sH(result,4);
            sL(result,3);sL(result,2);sL(result,1);sL(result,0);
        }
        else if(menu_index==32){
            sL(result,5);sL(result,4);
            sL(result,3);sL(result,2);sL(result,1);sL(result,0);
        }
    }
    else if(fuse_part==HFUSE){
        if(menu_index>=24){
            sH(result,4);
        }
        else{
            sL(result,4);
        }
    }

    result = ~result;
    return result;

}

u_int8_t m8::osc_set(u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    (void) hfuse_input;
    (void) efuse_input;

    u_int8_t result = 0;
    lfuse_input = ~lfuse_input;

    u_int8_t v_reg;
    bool cksel0 = iH(lfuse_input,0);
    bool cksel1 = iH(lfuse_input,1);
    bool cksel2 = iH(lfuse_input,2);
    bool cksel3 = iH(lfuse_input,3);
    bool sut0 = iH(lfuse_input,4);
    bool sut1 = iH(lfuse_input,5);
    v_reg = (cksel0 << 0) | (cksel1 << 1) | (cksel2 << 2) | (cksel3 << 3) | (sut0 << 4) | (sut1 << 5);

    if(v_reg== 0b111110){
        result = 0;
    }
    else if(v_reg== 0b101110){
        result = 1;
    }
    else if(v_reg== 0b011110){
        result = 2;
    }


    else if(v_reg== 0b111101){
        result = 3;
    }
    else if(v_reg== 0b101101){
        result = 4;
    }
    else if(v_reg== 0b011101){
        result = 5;
    }


    else if(v_reg== 0b111100){
        result = 6;
    }
    else if(v_reg== 0b101100){
        result = 7;
    }
    else if(v_reg== 0b011100){
        result = 8;
    }


    else if(v_reg== 0b111011){
        result = 9;
    }
    else if(v_reg== 0b101011){
        result = 10;
    }
    else if(v_reg== 0b011011){
        result = 11;
    }


    else if(v_reg== 0b111010){
        result = 12;
    }
    else if(v_reg== 0b101010){
        result = 13;
    }
    else if(v_reg== 0b011010){
        result = 14;
    }


    else if(v_reg== 0b111001){
        result = 15;
    }
    else if(v_reg== 0b101001){
        result = 16;
    }
    else if(v_reg== 0b011001){
        result = 17;
    }


    else if(v_reg== 0b111000){
        result = 18;
    }
    else if(v_reg== 0b101000){
        result = 19;
    }
    else if(v_reg== 0b011000){
        result = 20;
    }


    else if(v_reg== 0b110100){
        result = 21;
    }
    else if(v_reg== 0b100100){
        result = 22;
    }
    else if(v_reg== 0b010100){
        result = 23;
    }


    else if(v_reg== 0b110110){
        result = 24;
    }
    else if(v_reg== 0b100110){
        result = 25;
    }
    else if(v_reg== 0b010110){
        result = 26;
    }


    else if(v_reg== 0b100010){
        result = 27;
    }
    else if(v_reg== 0b010010){
        result = 28;
    }
    else if(v_reg== 0b000010){
        result = 29;
    }


    else if(v_reg== 0b100000){
        result = 30;
    }
    else if(v_reg== 0b010000){
        result = 31;
    }
    else if(v_reg== 0b000000){
        result = 32;
    }

    else{
        result = 33;
    }

    return result;
}

