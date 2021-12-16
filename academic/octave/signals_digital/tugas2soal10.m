close all
clear
clc

n = -6:0.4:6;
A = 3;
w = 2*pi*0.125;
y = A*sin(w*n+pi/5);

gambar1 = figure;
stem(n,y,'k')
axis([-6 6 -4.5 4.5])
xlabel('n')
ylabel('f[n]')