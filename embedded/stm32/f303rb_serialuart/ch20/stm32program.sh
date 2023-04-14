#!/usr/bin/bash

make -j$(nproc) clean
make -j$(nproc) all
st-flash --connect-under-reset erase
st-flash --reset --connect-under-reset --format ihex write ./build/ch.hex
