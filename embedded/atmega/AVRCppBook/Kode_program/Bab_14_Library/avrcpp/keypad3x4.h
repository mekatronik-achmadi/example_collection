//id:keypad3x4.h,keypad,2-8-2012,sidiknur@yahoo.com
//Atmega8,8MHz-internal

#ifndef KEYPAD3X4_H_INCLUDED
#define KEYPAD3X4_H_INCLUDED

#include "pinin.h"
#include "pinout.h"

template <port_id_t pcol0, uint8_t bcol0,
          port_id_t pcol1, uint8_t bcol1,
          port_id_t pcol2, uint8_t bcol2,

          port_id_t prow0, uint8_t brow0,
          port_id_t prow1, uint8_t brow1,
          port_id_t prow2, uint8_t brow2,
          port_id_t prow3, uint8_t brow3>
class Keypad3x4 : PinOut<pcol0,bcol0>,
                  PinOut<pcol1,bcol1>,
                  PinOut<pcol2,bcol2>,

                  PinIn<prow0,brow0,PULLUP>,
                  PinIn<prow1,brow1,PULLUP>,
                  PinIn<prow2,brow2,PULLUP>,
                  PinIn<prow3,brow3,PULLUP>
{
public:
    static inline uint8_t Get(void){

        uint8_t row;
        uint8_t col;

        for(col=0;col<3;col++){
            col_clear(col);
            row = row_get();
            if(row!=0x0f)
                break;
        }
        if(col==3 && row==0x0f)
            col=0x0f;

        return ((row<<4) | col);
    }

    static inline char GetLabel(uint8_t key){
        static char keypad_table[4][3]={{'1','2','3'},
                                        {'4','5','6'},
                                        {'7','8','9'},
                                        {'*','0','#'}};

        if(key==0xff)
            return '?';
        else
            return keypad_table[key>>4][key & 0x0f];
    }
private:
    typedef PinOut<pcol0,bcol0> COL0;
    typedef PinOut<pcol1,bcol1> COL1;
    typedef PinOut<pcol2,bcol2> COL2;

    typedef PinIn<prow0,brow0,PULLUP> ROW0;
    typedef PinIn<prow1,brow1,PULLUP> ROW1;
    typedef PinIn<prow2,brow2,PULLUP> ROW2;
    typedef PinIn<prow3,brow3,PULLUP> ROW3;

    static inline void col_clear(uint8_t col){
        COL0::Set();
        COL1::Set();
        COL2::Set();
        if(col==0)
            COL0::Clear();
        else if(col==1)
            COL1::Clear();
        else if(col==2)
            COL2::Clear();
    }

    static inline uint8_t row_get(){
        if(ROW0::IsClear())
            return 0;
        else if(ROW1::IsClear())
            return 1;
        else if(ROW2::IsClear())
            return 2;
        else if(ROW3::IsClear())
            return 3;
        else
            return 0x0f;
    }

};
#endif // KEYPAD3X4_H_INCLUDED
