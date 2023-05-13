#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jsmn.h"

#define TRUE    1
#define FALSE   0

#define EMPTY_JSON  TRUE

static jsmntok_t tkn[512];
static unsigned int calAmpl[6][2];

static const char *jsonAud =
#if EMPTY_JSON
"{\"audiogram\":{}}";
#else
"{\"audiogram\":{"
"\"ch_0\":{"
"\"freq_0\":{\"freq\": 0.625,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_1\":{\"freq\": 1.250,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_2\":{\"freq\": 2.500,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_3\":{\"freq\": 5.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_4\":{\"freq\":10.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_5\":{\"freq\":20.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}},"
"\"ch_1\":{"
"\"freq_0\":{\"freq\": 0.625,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_1\":{\"freq\": 1.250,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_2\":{\"freq\": 2.500,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_3\":{\"freq\": 5.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_4\":{\"freq\":10.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},"
"\"freq_5\":{\"freq\":20.000,\"ampl\":1,\"record\":[11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}}"
"}}";
#endif

static int jsonEq(const char *jsonSTR, jsmntok_t *tok, const char *str){

    if(tok->type==JSMN_STRING &&
      (int)strlen(str) == tok->end - tok->start &&
      strncmp(jsonSTR+tok->start, str, tok->end-tok->start)==0){

        return 0;
    }
    return -1;
}

static void getValue(int id){
    int i;
    for(i=1;i<id;i++){
      if (jsonEq(jsonAud, &tkn[i], "ampl") == 0) {
        printf("Value: %.*s",
               tkn[i + 1].end - tkn[i + 1].start,
               jsonAud + tkn[i + 1].start);
        printf(" at index %i\n",i);
      }
    }
}

static void loadArray(int id){
    int i;
    int m=0,n=0;
    char val[3];

    for(i=1;i<id;i++){
        if (jsonEq(jsonAud, &tkn[i], "ampl") == 0) {

            snprintf(val,sizeof(val),"%.*s\n",
                       tkn[i + 1].end - tkn[i + 1].start,
                        jsonAud + tkn[i + 1].start);

            calAmpl[m][n] = atoi(val);

            m++;
            if(m==6){
                m=0; n=1;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    int idx;
    int l,m,n;

    jsmn_parser prsr;
    jsmn_init(&prsr);

    idx = jsmn_parse(&prsr,
            jsonAud,
            strlen(jsonAud),
            tkn,
            sizeof(tkn)/sizeof(tkn[0]));

    if (idx < 0) {
        printf("Failed to parse JSON: %d\n", idx);
        return 1;
    }

    printf("%s\n",jsonAud);
    printf("idx= %i\n",idx);

    getValue(idx);
    loadArray(idx);

    for(l=0;l<12;l++){
        printf("%i\n",calAmpl[m][n]);

        m++;
        if(m==6){
            m=0; n=1;
        }
    }

    return 0;
}
