close all
clear
clc

n=-20:20;
x=((-1/2)^n)*(unit_step(n-4));
h=(4^n)*(unit_step(2-n));

figure
subplot(2,1,1)
stem(n,x)

subplot(2,1,2)
stem(n,h)

[no yo] = konvolusi(x,h,n);
figure
stem(no,yo)
xlim([-20 20])