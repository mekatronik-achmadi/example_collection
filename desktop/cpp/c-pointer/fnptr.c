#include <stdio.h>

void chVal(int *n){
    *n=5;
}

int main(int argc, char *argv[])
{
    int num = 2;

    printf("num %d\n",num);
    chVal(&num);
    printf("new num %d\n",num);

    return 0;
}
