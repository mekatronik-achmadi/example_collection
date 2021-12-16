[y,fs,bits]=wavread('Track 1_005.wav');
NFFT=256;
L=length(y);
T=1/fs;
t=(0:L-1)*T;
Y = fft(y,NFFT)/L;
f = fs/2*linspace(0,1,NFFT/2+1);

wname = 'haar';
scales = 1:NFFT/2;
[maxValue,indexMax] = max(abs(fft(y-mean(y))));
Frq = indexMax * Fs / L;

%Calculate Power density using Welch Power Density Function for each
%Frequency
 
%===========================================
figure(1);
h = spectrum.welch;
Hpsd = psd(h,y,'Fs',fs);
hLIN = plot(Hpsd);
xdata = get(hLIN,'xdata');
ydata = get(hLIN,'ydata');
[dummy,idxMax] = max(ydata);
FreqMax = xdata(idxMax);
hold on
ylim = get(gca,'Ylim');
plot([FreqMax,FreqMax],ylim,'m--')

%===========================================
figure(2);
subplot(211);plot(t,y);title('Ori-Signal');
title('Signal');
xlabel('Time or Space');
subplot(212);subplot(212);plot(f,2*abs(Y(1:NFFT/2+1))) ;title('FFT-ed');

%===========================================

figure(3);
coefs = cwt(y,scales,wname);
TAB_Sca2Frq = scal2frq(scales,wname,1/fs);
clf;
plot(TAB_Sca2Frq); axis tight; grid
hold on;

%===========================================

figure(4);
plot([scales(1),scales(end)],[Frq Frq],'m--');
set(gca,'Ylim',[0 100]);
title('Correspondence Table of Scales and Frequencies');
xlabel('Scale');
ylabel('Frequency');

%===========================================

figure(5);
[mini,idxSca] = min(abs(TAB_Sca2Frq-Frq));
Sca = scales(idxSca);

wscalogram('image',coefs,'scales',scales,'ydata',y);
hold on;
plot([1 size(coefs,2)],[Sca Sca],'Color','m','Linewidth',2);