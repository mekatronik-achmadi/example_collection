#!/bin/bash

cc -fPIC -shared -o libmyfunc.so myfunc.c
python myfunc.py
rm libmyfunc.so
