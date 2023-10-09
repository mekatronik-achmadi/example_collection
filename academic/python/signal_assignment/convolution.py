#!/usr/bin/python
# -*- coding: utf-8 -*-

def convolv(sign, conv):

    # Append 0 in beginning and end of signal array
    k = len(conv)-1
    zerosign = sign.copy()
    for i in range(k):
        zerosign.insert(0, 0)
        zerosign.append(0)

    # calculate all elements using previous modified array
    res = []
    for i in range(len(zerosign)-k):
        v = 0
        for j in range(len(conv)):
            v = v + conv[j] * zerosign[i+k-j]

        res.append(v)

    return res

print("Naive Implementation of Convolution")
print("Achmadi ST MT")
print("2410100085")

convo = [0,1,2,3]
signal = [0,1,2,3,4,5,6]

print(convolv(signal, convo))

