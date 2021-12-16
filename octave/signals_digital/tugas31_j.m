close all
clear
clc

n=-50:1:50;
n2=2*min(n):1:2*max(n);

x=((-1/2).^n).*(unit_step(n-4));
h=(4.^n).*(unit_step(2-n));

figure
subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,h,'.')

y=conv(x,h);
figure
stem(n2,y,'.','color','r')
xlim([-20 20])