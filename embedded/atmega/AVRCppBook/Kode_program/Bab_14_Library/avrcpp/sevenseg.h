//Id: sevenseg.h,Ver1.0,28Nov2011,sidiknur@yahoo.com
#ifndef SEVENSEG_H
#define SEVENSEG_H
/*
	 a
 	 ---
   f|   | b
	|_g_|
    |   | c
   e| d |
	 ---   h
*/
#define seg_a	0x01
#define seg_b	0x02
#define seg_c	0x04
#define seg_d	0x08
#define seg_e	0x10
#define seg_f	0x20
#define seg_g	0x40
#define seg_h	0x80

//angap bahwa seven segment berjenis common cathoda
#define num0	(uint8_t) ~(seg_g | seg_h)
#define num1	(uint8_t) (seg_b | seg_c)
#define num2	(uint8_t) ~(seg_f | seg_c | seg_h)
#define num3	(uint8_t) ~(seg_f | seg_e | seg_h)
#define num4	(uint8_t) (seg_f | seg_g | seg_b | seg_c)
#define num5	(uint8_t) ~(seg_b | seg_e | seg_h)
#define num6	(uint8_t) ~(seg_a | seg_b | seg_h)
#define num7	(uint8_t) (seg_f | seg_a | seg_b | seg_c)
#define num8	(uint8_t) ~seg_h
#define num9	(uint8_t) ~(seg_e | seg_d | seg_h)

typedef enum{
    COMMON_ANODA,
    COMMON_CATHODE
}sevenseg_common_t;

template<sevenseg_common_t common>
uint8_t sevenseg_pattern(uint8_t value){
    uint8_t seg_pattern[] = {num0,num1,num2,num3,num4,
							num5,num6,num7,num8,num9};
	return common==COMMON_CATHODE?seg_pattern[value % 10]:
                ~seg_pattern[value % 10];
}

#endif /* SEVENSEG_H */
