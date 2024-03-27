#include <stdio.h>

int *addTen(int *data){
    for(int i=0;i<5;i++){
        *(data+i)=*(data+i) + 10;
    }

    return data;
}

int main(int argc, char *argv[])
{
    int val[5] = {1,2,3,4,5};
    int *retVal;

    for (int i = 0; i < 5; ++i) {
        printf("%d ",*(val+i));
    }
    printf("\n");

    retVal = addTen(val);

    for (int i = 0; i < 5; ++i) {
        printf("%d ",*(retVal+i));
    }
    printf("\n");

    return 0;
}
