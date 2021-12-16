import numpy as np
import mle
import matplotlib.pyplot as plt

from data_all import DataAll

dat = DataAll()
dataR = dat.dataRed
dataG = dat.dataGreen
dataB = dat.dataBlue
dataC = dat.dataChlor
dataL = dat.dataLuminos

xR = mle.var('xR', observed=True, vector=True)
xG = mle.var('xG', observed=True, vector=True)
xB = mle.var('xB', observed=True, vector=True)
xL = mle.var('xL', observed=True, vector=True)
yC = mle.var('yC', observed=True, vector=True)

aR = mle.var('aR')
aG = mle.var('aG')
aB = mle.var('aB')
cG = mle.var('cG')
cL = mle.var('cL')
sigma = mle.var('sigma')

lumi_mod = mle.Normal(yC, aR*xR + aG*xG + aB*xB, sigma)
lumi_estim = lumi_mod.fit({'yC':dataC, 'xR':dataR, 'xG':dataG, 'xB':dataB},{'aR':1,'aG':1,'aB':1,'sigma':1})
lumi_coef = lumi_estim['x']
lumiY = lumi_coef['aR']*dataR + lumi_coef['aG']*dataG + lumi_coef['aB']*dataB

lumiG_mod = mle.Normal(yC, cG*xG, sigma)
lumiG_estim = lumiG_mod.fit({'yC':dataC,'xG':dataG},{'cG':1,'sigma':1})
lumiG_coef = lumiG_estim['x']
lumiGY = lumiG_coef['cG']*dataG

lumiL_mod = mle.Normal(yC, cL*xL, sigma)
lumiL_estim = lumiL_mod.fit({'yC':dataC,'xL':dataL},{'cL':1,'sigma':1})
lumiL_coef = lumiL_estim['x']
lumiLY = lumiL_coef['cL']*dataL

idx = dat.idx
plt.figure(1)
plt.title('Compare')
plt.plot(idx,dataC, 'k', label='measured')
plt.plot(idx,lumiY, 'b', label='estimation BGR')
plt.plot(idx,lumiGY, 'g', label='estimation Green')
plt.plot(idx,lumiLY, 'r', label='estimation Luminos')
plt.legend(loc='best')
plt.xlabel('Sample Number')
plt.ylabel('Chlorophil')
plt.grid()
plt.show()

x_axis = np.arange(0., 255, 1)
ln_lumiY = lumi_coef['aR']*x_axis + lumi_coef['aG']*x_axis + lumi_coef['aB']*x_axis
ln_lumiGY = lumiG_coef['cG']*x_axis
ln_lumiLY = lumiL_coef['cL']*x_axis

plt.figure(2)
plt.title('Linear Function')
plt.plot(x_axis,ln_lumiY, 'b', label='estimation BGR')
plt.plot(x_axis,ln_lumiGY, 'g', label='estimation Green')
plt.plot(x_axis,ln_lumiLY, 'r', label='estimation Luminos')
plt.legend(loc='best')
plt.xlabel('Pixel Value')
plt.ylabel('Chlorophil')
plt.grid()
plt.show()

plt.figure(3)
plt.title('Linear Function BGR')
plt.plot(x_axis,ln_lumiY, 'k')
plt.xlabel('Pixel Value')
plt.ylabel('Chlorophil')
plt.grid()
plt.show()

plt.figure(4)
plt.title('Linear Function Green')
plt.plot(x_axis,ln_lumiGY, 'k')
plt.xlabel('Pixel Value')
plt.ylabel('Chlorophil')
plt.grid()
plt.show()

plt.figure(5)
plt.title('Linear Function Luminos')
plt.plot(x_axis,ln_lumiLY, 'k')
plt.xlabel('Pixel Value')
plt.ylabel('Chlorophil')
plt.grid()
plt.show()