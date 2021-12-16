close all
clear
clc

n = [-6:1:7];
n2=2*min(n):1:2*max(n);

x=[zeros(1,5) 1 1 0 1 1 zeros(1,4)];
h=[zeros(1,4) 1 2 3 2 1 zeros(1,5)];

figure
subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,h,'.')

y=conv(x,h);
figure
stem(n2,y,'.','color','r')