#!/usr/bin/python3
# -*- coding: utf-8 -*-

import ctypes

NUM = 16

fungsi = ctypes.CDLL("./libmyfunc.so")
fungsi.fungsiSaya.argtypes = [ctypes.c_int]

retVal = fungsi.fungsiSaya(NUM)
print(retVal)
