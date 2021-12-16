close all
clear
clc

fs=100;
n=0:1/fs:4

x=cos(40*pi*n)+cos(0.5*pi*n)-cos(0.75*pi*n)+2*sin(5*pi*n);
figure
plot(n,x,'linewidth',1,'color',[255 0 0]/255)

N=2^nextpow2(length(x));
m=-N/2:(N/2)-1;
w=2*pi*fs*m/N;

X=x*exp(-1i*2*pi*n'*m*fs/N);
figure
plot(w/(2*pi),abs(X),'linewidth',1,'color',[0 0 255]/255)
xlim([-100 100])