# -*- coding: utf-8 -*-

import os

class MyGPIO:
    def __init__(self):
        pass
        
    def setup(self, pin, direction):
        cmd = "echo " + str(pin) + " >  /sys/class/gpio/export"
        os.system(cmd)
        
        if direction == 0:
           cmd = "echo in > /sys/class/gpio/gpio" + str(pin) + "/direction" 
        elif direction == 1:
            cmd = "echo out > /sys/class/gpio/gpio" + str(pin) + "/direction" 
        
        os.system(cmd)
        
        return
        
    def value(self, pin, val):
        cmd = "echo " + str(val) + " > /sys/class/gpio/gpio" + str(pin) + "/value"
        os.system(cmd)
        return
    
