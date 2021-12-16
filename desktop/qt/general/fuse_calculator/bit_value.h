#ifndef BIT_VALUE_H
#define BIT_VALUE_H

#define _BV(bit) (1 << bit)
#define iH(reg,bit) (reg & (_BV(bit)))
#define sH(reg,bit) reg|=_BV(bit)
#define sL(reg,bit) reg&=~_BV(bit)

#define LFUSE 0
#define HFUSE 1
#define EFUSE 2

#endif // BIT_VALUE_H
