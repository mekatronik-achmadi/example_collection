close all
clear
clc

t = -1:0.01:1;
A = 3;
w = 2*pi*2;
y = A*sin(w*t+pi/2);

gambar1 = figure;
plot(t,y)
axis([-1 1 -4.5 4.5])
xlabel('t')
ylabel('f(t)')