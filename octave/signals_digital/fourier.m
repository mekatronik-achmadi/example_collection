close all
clear
clc

tic
fs=200
t=-5:1/fs:5;
N=5;
n=1:N;
ao=10;
an=10*sin(pi*n)./(pi*n);
bn=20*(sin(pi*n/2)).^2./(pi*n);

x=(ao/2)+an*cos(pi*n'*t)+bn*sin(pi*n'*t);
figure
plot(t,x,'linewidth',1,'color',[0 0 255]/255)
toc