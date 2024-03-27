#include <stdio.h>

int main(void)
{
    int var = 5, *adrVar;

    adrVar = &var;

    printf("var %d\n",var);
    printf("addr var %p\n",adrVar);
    printf("value of adrVar %d\n",*adrVar);
    printf("adrr of adrVar %p\n",&adrVar);

    *adrVar = 9;

    printf("new var %d\n",var);
    printf("new addr var %p\n",adrVar);
    printf("new value of adrVar %d\n",*adrVar);
    printf("new adrr of adrVar %p\n",&adrVar);

    return 0;
}
