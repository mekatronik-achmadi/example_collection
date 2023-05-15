#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *strTest = "8,90,80,70,69,50,40,30,20\r\n";

unsigned int num;
unsigned int valR[4];
unsigned int valL[4];

int main(int argc, char *argv[])
{
    unsigned i,j,cnt;
    char strNew[9][4];

    j=0; cnt=0;
    for(i=0;i<=strlen(strTest);i++){
        if(strTest[i]==',' || strTest[i]=='\0'){
            strNew[cnt][j]='\0';
            cnt++;
            j=0;
        }
        else{
            strNew[cnt][j]=strTest[i];
            j++;
        }
    }

    for(i=0;i<cnt;i++){
        if(i==0) num = atoi(strNew[i]);

        if((i>0) && (i<5)) valL[i-1] = atoi(strNew[i]);
        else if(i>=5) valR[i-5] = atoi(strNew[i]);
    }

    printf("%i %i %i %i %i %i %i %i %i\n",
            num,
            valL[0], valL[1], valL[2], valL[3],
            valR[0], valR[1], valR[2], valL[3]);

    return 0;
}
