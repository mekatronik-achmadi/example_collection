close all
clear
clc

n = [-2:1:20];
n2=2*min(n):1:2*max(n);

x=[zeros(1,2) ones(1,5) zeros(1,16)];
h=[zeros(1,4) ones(1,6) zeros(1,3) ones(1,6) zeros(1,4)];

figure
subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,h,'.')

y=conv(x,h);
figure
stem(n2,y,'.','color','r')


