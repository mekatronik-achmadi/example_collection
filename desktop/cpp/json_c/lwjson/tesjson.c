#include <stdio.h>

#include "lwjson.h"

static lwjson_token_t tokens[512];
static lwjson_t lwjson;

static char *strJSON =  "{\"mykey\":\"myvalue\"}";

static void example_minimal_run(void){
    lwjson_init(&lwjson, tokens, LWJSON_ARRAYSIZE(tokens));

    if(lwjson_parse(&lwjson,strJSON)== lwjsonOK){
        const lwjson_token_t *tkn;
        printf("JSON parsed \n");

        if((tkn = lwjson_find(&lwjson,"mykey"))!=NULL){
            printf("Key found with data type: %d\n",(int)tkn->type);
        }
    }

    lwjson_free(&lwjson);
}

int main(int argc, char *argv[])
{
    example_minimal_run();
    return 0;
}
