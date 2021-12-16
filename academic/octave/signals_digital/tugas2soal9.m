close all
clear
clc

n = -5:0.4:5;
A = 3;
w = 2*pi*0.125;
y = A*cos(w*n+pi/4);

gambar1 = figure;
stem(n,y)
axis([-5 5 -4.5 4.5])
xlabel('n')
ylabel('f[n]')