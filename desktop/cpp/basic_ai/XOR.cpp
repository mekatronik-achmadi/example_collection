#include <stdio.h>
#include <conio.h>


int classifi(int net,int thres)
    {
    if(net > thres)
        return 1;
    else if(net < -thres)
        return -1;
    else
        return 0;
    }
    

int main(void)
    {
    printf("Jaringan syaraf tiruan ,metode perceptron\n");
    printf("Pengenalan fungsi XOR\n");
    printf("-------------------------------------------\n");
    int bias,b1,b2,alpha,theta,net,out,dbias,db1,db2;
    int t[4] = {-1,1,1,-1};
    int x1[4] = {1,1,0,0};
    int x2[4] = {1,0,1,0};
    
    //inisailisasi
    printf("Bias awal     : "); scanf("%d", &bias);
    printf("Bobot 1       : "); scanf("%d", &b1);
    printf("Bobot 2       : "); scanf("%d", &b2);
    printf("Learning Rate : "); scanf("%d", &alpha);
    printf("Threshold     : "); scanf("%d", &theta);
    
    int i,j;
    for(i=0;i<=12;i++)
        {
        printf("\n\nEpoch-%d\n",i);
        printf("   x1    x2     t     net    out   Delta bobot dan bias    bobot dan bias\n");
        for(j=0;j<4;j++)
           {
           int temp1,temp2,temp3;
           temp1 = bias;
           temp2 = b1;
           temp3 = b2;
           net = bias + b1*x1[j] + b2*x2[j];
           out = classifi(net,theta);
           if(out == t[j]){
                  bias = bias;
                  b1 = b1;
                  b2 = b2;
                  }
           else {
                  bias = bias + alpha*t[j];
                  b1 = b1 + alpha*t[j]*x1[j];
                  b2 = b2 + alpha*t[j]*x2[j];
                }
           
           dbias = bias - temp1;
           db1 = b1 - temp2;
           db2 = b2 - temp3;
  
           printf(" %3.1d   %3.1d    %3.1d    %3.1d    %3.1d     %3.1d   %3.1d  %3.1d        %3.1d  %3.1d  %3.1d\n",
                                     x1[j],x2[j],t[j],net,out,db1,db2,dbias,b1,b2,bias);
           }
           printf("\n");
           }
    
    getch();
    return 0;
}
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
