#include "chip.h"

extern u_int8_t val_EFUSE;
extern u_int8_t val_HFUSE;
extern u_int8_t val_LFUSE;

chip::chip()
{

}

QStringList chip::list(){
    QStringList list;

    list << "ATMega2560";   //0
    list << "ATMega2561";   //1

    list << "ATMega1281";   //2
    list << "ATMega1280";   //3
    list << "ATMega128";    //4

    list << "ATMega6490";   //5
    list << "ATMega649";    //6
    list << "ATMega644";    //7
    list << "ATMega640";    //8
    list << "ATMega64";     //9

    list << "ATMega48";     //10

    list << "ATMega3290";   //11
    list << "ATMega329";    //12
    list << "ATMega328P";   //13
    list << "ATMega324P";   //14
    list << "ATMega324";    //15
    list << "ATMega32";     //16

    list << "ATMega169";    //17
    list << "ATMega168";    //18
    list << "ATMega164";    //19
    list << "ATMega162";    //20
    list << "ATMega16";     //21

    list << "ATMega8535";   //22
    list << "ATMega8515";   //23
    list << "ATMega88";     //24
    list << "ATMega8";      //25

    return list;
}

u_int8_t chip::fuse_default(u_int8_t chip_index, u_int8_t fuse_part){
    u_int8_t result=0x00;

    switch(chip_index){
    case 25: result = v_m8.fuse_default(fuse_part);break;
    case 23: result = v_m8515.fuse_default(fuse_part);break;
    default: result=0xFF;
    }

    return result;
}

u_int8_t chip::fuse_restrict(u_int8_t chip_index, u_int8_t fuse_part){
    u_int8_t result=0x00;

    switch(chip_index){
    case 25: result = v_m8.fuse_restrict(fuse_part);break;
    case 23: result = v_m8515.fuse_restrict(fuse_part);break;
    default: result=0xFF;
    }

    return result;
}

QStringList chip::fuse_string(u_int8_t chip_index, u_int8_t fuse_part){
    QStringList result;

    switch(chip_index){
    case 25: result = v_m8.fuse_string(fuse_part);break;
    case 23: result = v_m8515.fuse_string(fuse_part);break;
    default:
        u_int8_t i;
        for(i=0;i<8;i++){
            result << "UNUSED";
        }
    }

    return result;
}

QStringList chip::fuse_tooltip(u_int8_t chip_index, u_int8_t fuse_part){
    QStringList result;

    switch(chip_index){
    case 25: result = v_m8.fuse_tooltip(fuse_part);break;
    case 23: result = v_m8515.fuse_tooltip(fuse_part);break;
    default:
        u_int8_t i;
        for(i=0;i<8;i++){
            result << "UNUSED";
        }
    }
    return result;
}

QStringList chip::bod_string(u_int8_t chip_index){
    QStringList result;

    switch(chip_index){
    case 25: result = v_m8.bod_string();break;
    case 23: result = v_m8515.bod_string();break;
    default: result << "UNUSED";
    }

    return result;
}

u_int8_t chip::bod_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.bod_get(fuse_part,fuse_input,menu_index);break;
    case 23: result = v_m8515.bod_get(fuse_part,fuse_input,menu_index);break;
    default: result = fuse_input;
    }

    return result;
}

u_int8_t chip::bod_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.bod_set(lfuse_input,hfuse_input,efuse_input);break;
    case 23: result = v_m8515.bod_set(lfuse_input,hfuse_input,efuse_input);break;
    default: result = 0;
    }

    return result;
}

QStringList chip::bootsz_string(u_int8_t chip_index){
    QStringList result;

    switch(chip_index){
    case 25: result = v_m8.bootsz_string();break;
    case 23: result = v_m8515.bootsz_string();break;
    default: result << "UNUSED";
    }

    return result;
}

u_int8_t chip::bootsz_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.bootsz_get(fuse_part,fuse_input,menu_index);break;
    case 23: result = v_m8515.bootsz_get(fuse_part,fuse_input,menu_index);break;
    default: result = fuse_input;;
    }

    return result;
}

u_int8_t chip::bootsz_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.bootsz_set(lfuse_input,hfuse_input,efuse_input);break;
    case 23: result = v_m8515.bootsz_set(lfuse_input,hfuse_input,efuse_input);break;
    default: result = 0;
    }

    return result;
}

QStringList chip::osc_string(u_int8_t chip_index){
    QStringList result;

    switch(chip_index){
    case 25: result = v_m8.osc_string();break;
    case 23: result = v_m8515.osc_string();break;
    default: result << "UNUSED";
    }

    return result;
}

u_int8_t chip::osc_get(u_int8_t chip_index, u_int8_t fuse_part, u_int8_t fuse_input, u_int8_t menu_index){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.osc_get(fuse_part,fuse_input,menu_index);break;
    case 23: result = v_m8515.osc_get(fuse_part,fuse_input,menu_index);break;
    default: result = fuse_input;
    }

    return result;
}

u_int8_t chip::osc_set(u_int8_t chip_index, u_int8_t lfuse_input, u_int8_t hfuse_input, u_int8_t efuse_input){
    u_int8_t result;

    switch(chip_index){
    case 25: result = v_m8.osc_set(lfuse_input,hfuse_input,efuse_input);break;
    case 23: result = v_m8515.osc_set(lfuse_input,hfuse_input,efuse_input);break;
    default: result = 0;
    }

    return result;
}
