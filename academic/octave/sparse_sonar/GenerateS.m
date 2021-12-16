function [s fs] = GenerateS()
%Code to generate the transmit waveform s(t) used in the acoustic imaging

T=1;
N=16;
alpha=0;
fs=96000;

% generate ideal PN Code for transmission
[s seq sequence Ns] = MakePNWaveform(T,N,alpha,fs);

fs = 96000; %sample rate

L = 160;
fsa = 0.025;
fpa = 0.05; %0.05*nyquist = 2.4 kHz
fpb = 0.6;

%0.6 *nyquist = 28.8 kHz
fsb = 0.65;
dels = 3e-5; %90dB stopband attentuation
delp = 0.8279; %10% passband variation allowed

%create LS FIR Bandpass Filter
F = [0,fsa,fpa,fpb,fsb,1];
A = [0,0,1,1,0,0];
W = [1/dels,1/delp,1/dels];

hbp = firls(L,F,A,W);

s = real(ifft(fft(s).*fft(hbp,length(s))));

end

