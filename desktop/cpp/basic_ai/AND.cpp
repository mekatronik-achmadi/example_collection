#include <stdio.h>
#include <conio.h>


int classifi(float net,float thres)
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
    FILE *ftulis;
    char namefile[30] = "JST_AND_PERCEPTRON.txt";
    if( (ftulis = fopen(namefile,"w")) == NULL ){
        printf("Penulisan / Pembuatan file gagal\n\n");
        return 1;
        }
    else{
    printf("Penulisan / Pembuatan file berhasil\n\n");
    fprintf(ftulis,"Jaringan syaraf tiruan ,metode perceptron\n");
    fprintf(ftulis,"Pengenalan fungsi AND\n");
    fprintf(ftulis,"-------------------------------------------\n");
    float bias,b1,b2,alpha,theta,net,dbias,db1,db2;
    int out;
    int t[4] = {1,-1,-1,-1};
    int x1[4] = {1,1,0,0};
    int x2[4] = {1,0,1,0};
    
    //inisailisasi
    printf("Bias awal     : "); scanf("%f", &bias);
    printf("Bobot 1       : "); scanf("%f", &b1);
    printf("Bobot 2       : "); scanf("%f", &b2);
    printf("Learning Rate : "); scanf("%f", &alpha);
    printf("Threshold     : "); scanf("%f", &theta);
    
    fprintf(ftulis,"Bias awal     : %f\n", bias); 
    fprintf(ftulis,"Bobot 1       : %f\n",b1); 
    fprintf(ftulis,"Bobot 2       : %f\n",b2); 
    fprintf(ftulis,"Learning Rate : %f\n",alpha); 
    fprintf(ftulis,"Threshold     : %f\n",theta); 
    
    int i,j;
    for(i=0;i<=12;i++)
        {
        fprintf(ftulis,"\n\nEpoch-%d\n",i);
        fprintf(ftulis,"   x1    x2     t     net    out   Delta bobot dan bias    bobot dan bias\n");
        for(j=0;j<4;j++)
           {
           float temp1,temp2,temp3;
           temp1 = bias;
           temp2 = b1;
           temp3 = b2;
           net = (float)(bias + b1*x1[j] + b2*x2[j]);
           out = classifi(net,theta);
           if(out == t[j]){
                  bias = bias;
                  b1 = b1;
                  b2 = b2;
                  }
           else {
                  bias =(float)( bias + alpha*t[j]);
                  b1 =(float)( b1 + alpha*t[j]*x1[j]);
                  b2 =(float)( b2 + alpha*t[j]*x2[j]);
                }
           
           dbias = bias - temp1;
           db1 = b1 - temp2;
           db2 = b2 - temp3;
  
           fprintf(ftulis," %3.1d   %3.1d    %3.1d    %3.1f    %3.1d     %3.1f   %3.1f  %3.1f        %3.1f  %3.1f  %3.1f\n",
                                     x1[j],x2[j],t[j],net,out,db1,db2,dbias,b1,b2,bias);
           }
           fprintf(ftulis,"\n");
           }
           fclose(ftulis);
         }
    
    getch();
    return 0;
}
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
