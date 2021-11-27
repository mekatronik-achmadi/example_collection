#!/bin/bash

sudo avrdude -D -v -v -p m2560 -c stk500v2 -U flash:w:las_orbit.hex:i -P /dev/ttyACM0
