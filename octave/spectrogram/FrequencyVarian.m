close all;
clear all;
clc;

%======================= Data Entry ======================

[y,fs,bits]=wavread('Track 1_005.wav');
NFFT=256;

%====== wideband (More Window Length, Less Overlap) =========
wideHamm=Hamming(NFFT);
wideOverlap=NFFT/16;

%====== narrowband (Less Window Length, More Overlap) ==========
narrowHamm=Hamming(NFFT/4);
narrowOverlap=NFFT/8;

%====== Plot Original and his FFT ============
L=length(y);
T=1/fs;
t=(0:L-1)*T;
Y = fft(y,NFFT)/L;
f = fs/2*linspace(0,1,NFFT/2+1);

figure(1);
subplot(211);plot(t,y);title('Ori-Signal');
subplot(212);plot(f,2*abs(Y(1:NFFT/2+1))) ;title('FFT-ed');

%====== Plot each spectrum=========

figure(2);
subplot(211);specgram(y,NFFT,fs,wideHamm,wideOverlap);title('WideBand Fs=default 44100');
subplot(212);specgram(y,NFFT,fs,narrowHamm,narrowOverlap); title('NarrowBand Fs=default 44100');

Fs=8000;
figure(3);
subplot(211);specgram(y,NFFT,Fs,wideHamm,wideOverlap);title(['WideBand Fs= ' num2str(Fs)]);
subplot(212);specgram(y,NFFT,Fs,narrowHamm,narrowOverlap); title(['NarrowBand Fs= ' num2str(Fs)]);

Fs=11025;
figure(4);
subplot(211);specgram(y,NFFT,Fs,wideHamm,wideOverlap);title(['WideBand Fs= ' num2str(Fs)]);
subplot(212);specgram(y,NFFT,Fs,narrowHamm,narrowOverlap); title(['NarrowBand Fs= ' num2str(Fs)]);

Fs=16000;
figure(5);
subplot(211);specgram(y,NFFT,Fs,wideHamm,wideOverlap);title(['WideBand Fs= ' num2str(Fs)]);
subplot(212);specgram(y,NFFT,Fs,narrowHamm,narrowOverlap); title(['NarrowBand Fs= ' num2str(Fs)]);

Fs=22050;
figure(5);
subplot(211);specgram(y,NFFT,Fs,wideHamm,wideOverlap);title(['WideBand Fs= ' num2str(Fs)]);
subplot(212);specgram(y,NFFT,Fs,narrowHamm,narrowOverlap); title(['NarrowBand Fs= ' num2str(Fs)]);