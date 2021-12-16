#include <stdio.h>
#include <inttypes.h>

/**
 * @brief Use Pointer Basic example
 */
#define BASIC	0

/**
 * @brief Use Pointer Array example
 */
#define ARRAY	1

/**
 * @brief Use Pointer Pass by Value/Reff example
 */
#define PASSBY	2

/**
 * @brief Used Example part
 */
#define EXAMPLE PASSBY

/**
 * @brief Example a function using pass by value
 * @param[in] uint8_t input
 * @return uint8_t result
 */
uint8_t passByValue(uint8_t input){
    return input + 5;
}

/**
 * @brief Example a function using pass by reference
 * @param[in] uint8_t input pointer
 */
void passByReff(uint8_t *input){
    *input = *input + 5;
}

int main(void){

#if EXAMPLE==BASIC
    uint8_t*	ptr_i;
    uint8_t		val_i;

    val_i = 10;
    ptr_i = &val_i;

    printf("addr of val_i: %p \r\n",	&val_i);
    printf("value in val_i: %i \r\n",	val_i);

    /*-----------------------------------*/

    printf("\r\n");
    printf("addr in ptr_i: %p \r\n",	ptr_i);
    printf("value at ptr_i: %i \r\n",	*ptr_i);
    printf("addr of ptr_i itself: %p \r\n",	&ptr_i);

    /*-----------------------------------*/

    printf("\r\n");
    *ptr_i = 15;

    printf("Modify val_i using ptr_i \r\n");
    printf("new value in val_i: %i \r\n",	val_i);
    printf("new value at ptr_i: %i \r\n",	*ptr_i);
    printf("same addr in ptr_i: %p \r\n",	ptr_i);

#elif EXAMPLE==ARRAY
    uint8_t var_arr[] = {2,4,6,8};
    uint8_t* ptr_arr;

    ptr_arr = &var_arr[0];
    printf("value at ptr_arr: %i \r\n", *ptr_arr);
    printf("addr in ptr_arr: %p \r\n", ptr_arr);

    /*-----------------------------------*/

    ptr_arr = ptr_arr+1;
    printf("\r\n");
    printf("value at next ptr_arr: %i \r\n", *ptr_arr);
    printf("addr in ptr_arr: %p \r\n", ptr_arr);

    /*-----------------------------------*/

    *ptr_arr = *ptr_arr+1;
    printf("\r\n");
    printf("new value at ptr_arr addr: %i \r\n", *ptr_arr);
    printf("addr in ptr_arr: %p \r\n", ptr_arr);

#elif EXAMPLE==PASSBY
    uint8_t val = 10;
    uint8_t res;

    res = passByValue(val);
    printf("result byValue is %i \r\n", res);

    passByReff(&val);
    printf("result byReff is %i \r\n", val);

#endif

    return 0;
}
