#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *val;
    printf("amount:");
    scanf("%d",&n);

    val = (int*) malloc(n*sizeof(int));

    for(int i=0;i<n;i++) *(val+i) = i;

    for(int i=0;i<n;i++) printf("%d ",*(val+i));
    printf("\n");

    free(val);

    return 0;
}
