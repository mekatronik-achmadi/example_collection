#/bin/bash

gcc -c -o lwjson.o lwjson.c
gcc -c -o tesjson.o tesjson.c
gcc -o tesjson tesjson.o lwjson.o
