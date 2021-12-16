#!/bin/bash

gcc -O3 -fPIC -shared -o libcsum.so c_sum.c
python c_sum.py
rm libcsum.so
