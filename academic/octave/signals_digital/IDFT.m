close all
clear
clc

a= 30;
wcut=20;

fs=10;
n=0:1/fs:1;
x=sin(a*n)/(pi*n);
figure
subplot(3,1,1)
plot(n,x)

N=2^nextpow2(length(x));
m=(-N/2):(N/2)-1;
w=2*pi*m*fs/N;
X=x*exp(-1i*n'*w);
subplot(3,1,2)
plot (w/(2*pi),abs(X))
xlim([-80 80])

y=(1/N)*X*exp(1i*w'*n);
y=real(y);
subplot(3,1,3)
plot(n,y)

filterku=w/(2*pi)>-20 & w/(2*pi)<20;
figure
subplot(3,1,1)
plot(w/(2*pi), filterku)
xlim([-80 80])
ylim ([0 1.25])
ynew=(1/N)*(X.*filterku)*exp(1i*w'*n);
ynew=real(ynew);
subplot(3,1,2)
plot(n,ynew)

Nnew=2^nextpow2(length(ynew));
mnew=(-Nnew/2):(Nnew/2)-1;
wnew=2*pi*m*fs/N;
Ynew=ynew*exp(-1i*n'*wnew);
subplot(3,1,3)
plot (wnew/(2*pi),abs(Ynew))
xlim([-80 80])
