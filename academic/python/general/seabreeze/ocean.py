#import seabreeze
#seabreeze.use("pyseabreeze")
#import seabreeze.spectrometers as sb

from seabreeze.backends import _use_cseabreeze
_lib = _use_cseabreeze()
if _lib is not None and _lib.device_list_devices():
    pass  # cseabreeze import works and it finds a spectrometer
else:
    # cseabreeze import failed or it didn't find a spectrometer
    import seabreeze
    seabreeze.use("pyseabreeze")

# continue normally
import seabreeze.spectrometers as sb

import time
import pandas as pd
import numpy as np

devices = sb.list_devices()
print(devices)

filename = "data.csv"
delay = 1 #second
duration = 10 #second

spec = sb.Spectrometer.from_first_available()
spec.integration_time_micros(20000)

wavelength = spec.wavelengths()

df = pd.DataFrame(columns = wavelength)

for i in range(int(duration/delay)):
    val = spec.intensities()
    print(wavelength[np.argmax(val)], max(val))
    df.loc[i] = val
    time.sleep(delay)
    

df.to_csv(filename)
