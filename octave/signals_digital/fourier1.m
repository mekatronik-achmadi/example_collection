close all
clear
clc

fs=1000;
n=0:1/fs:2
x=sin(2*pi*20*n);
subplot(211);
plot(n,x)
N=2^nextpow2(length(x));
m=-N/2:(N/2)-1;
w=2*pi*fs*m/N;
X=x*exp(-1i*2*pi*n'*m*fs/N);
subplot(212);
plot(w/(2*pi),abs(X))
xlim([-70 70])