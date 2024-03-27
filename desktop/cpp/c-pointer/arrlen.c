#include <stdio.h>

int main(int argc, char *argv[])
{
    int val[5],len,*ptrlen;

    len = sizeof(val)/sizeof(val[0]);
    printf("The Array Length %d\n",len);

    return 0;
}
