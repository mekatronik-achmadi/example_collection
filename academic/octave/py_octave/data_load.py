import numpy as np
#import scipy.io as sio
from oct2py import octave as oc
import matplotlib.pyplot as plt

class DataLoad:
    def __init__(self,n_start,n_stop):
        #input_data=sio.loadmat("data_input.mat")['input_data']
        #output_data=sio.loadmat("data_output.mat")['output_data']
        input_data= oc.data_input
        output_data= oc.data_output
        
        u_11 = input_data[n_start:n_stop,1]
        u_12 = input_data[n_start:n_stop,3]
        u_13 = input_data[n_start:n_stop,2]
        
        y_11 = output_data[n_start:n_stop,1]
        y_12 = output_data[n_start:n_stop,2]
                
        self.u11 = u_11/u_11.max()
        self.u12 = u_12/u_12.max()
        self.u13 = u_13/u_13.max()
        self.y11 = y_11/y_11.max()
        self.y12 = y_12/y_12.max()
        
        self.t = np.arange(0,n_stop-n_start,1)
        self.dim = np.shape(self.t)[0]
        
    def plot(self):
        plt.figure()
        plt.title('Measured')
        plt.subplot(5, 1, 1)
        plt.plot(self.u11)
        plt.ylabel('Input 1')
        plt.subplot(5, 1, 2)
        plt.plot(self.u12)
        plt.ylabel('Input 2')
        plt.subplot(5, 1, 3)
        plt.plot(self.u13)
        plt.ylabel('Input 3')
        plt.subplot(5, 1, 4)
        plt.plot(self.y11)
        plt.ylabel('Output 1')
        plt.subplot(5, 1, 5)
        plt.plot(self.y12)
        plt.ylabel('Output 2')
        
        plt.xlabel('Data Series')
        plt.show()
