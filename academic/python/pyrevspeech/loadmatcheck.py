#!/bin/python

import sys
from scipy.io import loadmat

in_mat = sys.argv[1]  # input IR Matlab
IR = loadmat(in_mat, squeeze_me=True,struct_as_record=False)

print("All Mat Dictionary:")
print(IR)

print("--------------------------")

keys = list(IR.keys())
print("Available Keys:")
print(keys)

print("--------------------------")

for i in range(0,len(keys)):
    print("Content of %i index" % i)
    print(IR[keys[i]])
