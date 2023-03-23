#!/bin/python

import numpy as np
from scipy import signal
import sys
import os
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


