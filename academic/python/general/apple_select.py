#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import inspect

## Problem modelling
# Condition: 8 Apples
# Objective: Get 5 Good Apples

## Good Apples example
#
good = 5

## Bad Apples example
#
bad = 3

# list possible cases
case0 = np.array([bad, good, good, good, good, good, good, good])
case1 = np.array([good, bad, good, good, good, good, good, good])
case2 = np.array([good, good, bad, good, good, good, good, good])
case3 = np.array([good, good, good, bad, good, good, good, good])
case4 = np.array([good, good, good, good, bad, good, good, good])
case5 = np.array([good, good, good, good, good, bad, good, good])
case6 = np.array([good, good, good, good, good, good, bad, good])
case7 = np.array([good, good, good, good, good, good, good, bad])

## Just to retrieve variable name
#
# Ignore this
def retrieve_name(var):
    for fi in reversed(inspect.stack()):
         names = [var_name for var_name, var_val in fi.frame.f_locals.items() if var_val is var]
         if len(names) > 0:
             return names[0]

## Select 5 Good Apples
#
def SelectProcess(caseArray):
    # Just variable print
    print('5 Good Apples in %s: ' % retrieve_name(caseArray),end='')

    # First Measurement
    X = caseArray[0] + caseArray[1] + caseArray[2] + caseArray[3] + caseArray[4]

    # Second Measurement
    Y = caseArray[3] + caseArray[4] + caseArray[5] + caseArray[6] + caseArray[7]

    # if bad apple in index 3 or 4
    if X == Y:
        print("First 3+Last 2, or First 2+Last 3", end='')

        remDiv = X % 4
        valDiv = (X - remDiv) / 4

        if remDiv > valDiv:
            print(" and bad Apple is bigger")
        elif remDiv < valDiv:
            print(" and bad Apple is smaller")

        return

    # if bad apple in other index
    if X != Y:
        if X % 5 == 0:
            print("All in First measurement",end='')

            if Y > X:
                print(" and bad Apple is bigger")
            elif Y < X:
                print(" and bad Apple is smaller")

            return

        if Y % 5 == 0:
            print("All in Second measurement",end='')

            if X > Y:
                print(" and bad Apple is bigger")
            elif X < Y:
                print(" and bad Apple is smaller")

            return

SelectProcess(case0)
SelectProcess(case1)
SelectProcess(case2)
SelectProcess(case3)
SelectProcess(case4)
SelectProcess(case5)
SelectProcess(case6)
SelectProcess(case7)
