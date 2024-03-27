#include <stdio.h>

void swapNum(int *a,int *b){
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

int main(int argc, char *argv[])
{
    int vA=5,vB=6;
    printf("A %d | B %d\n",vA,vB);
    swapNum(&vA, &vB);
    printf("new A %d | B %d\n",vA,vB);

    return 0;
}
