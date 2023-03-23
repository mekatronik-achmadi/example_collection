#!/bin/python

import numpy as np
from scipy import signal
import sys
import os
#from scipy.io import wavfile
import soundfile as sf

# Load support lib
from supplib import ReadList
from supplib import copy_folder
from supplib import load_IR
from supplib import shift

# Reading input arguments
in_folder = sys.argv[1]  # input folder
out_folder = sys.argv[2]  # output folder
list_file = sys.argv[3]  # list file ("wav_file IR_file")


# Read List file
[list_sig, list_ir] = ReadList(list_file)

# Replicate input folder structure to output folder
copy_folder(in_folder, out_folder)

for i in range(len(list_sig)):

    # Open clean wav file
    [signal_clean, fs] = sf.read(list_sig[i])
    #[fs, signal_clean] = wavfile.read(list_sig[i])

    # Signal normalization
    signal_clean = signal_clean / np.max(np.abs(signal_clean))

    # Open Impulse Response (IR)
    IR = load_IR(list_ir[i])
