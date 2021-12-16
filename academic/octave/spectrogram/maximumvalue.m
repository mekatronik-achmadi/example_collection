close all;
clear all;
clc;

[y,Fs,bits]=wavread('Track 1_005.wav');
NFFT=256;
L=length(y);

%Parseval theorem tells that if you perform the integral of the squared modules of the Fourier coefficients, 
%then divide this area with the time windows T (or N segments of data chops) during which you record the signal, 
%then you retrieve the signal average power.

Cfou=fft(y,NFFT);

sqCfou=abs(Cfou).^2;

sumsqCfou=0;
for i=1:length(sqCfou);
    sumsqCfou=sumsqCfou+sqCfou(i);
end

pow=Fs/NFFT*sumsqCfou;
avepow=pow/L;

%Calculate Power density using Welch Power Density Function for each
%Frequency

h = spectrum.welch;
Hpsd = psd(h,y,'Fs',Fs);
hLIN = plot(Hpsd);
xdata = get(hLIN,'xdata');
ydata = get(hLIN,'ydata');
[dummy,idxMax] = max(ydata);
FreqMax = xdata(idxMax);
hold on
ylim = get(gca,'Ylim');
plot([FreqMax,FreqMax],ylim,'m--')


