close all
clear
clc

t = -5:0.01:5;
A = 2;
w = 2*pi*0.25;
y = A*sin(w*t+pi/3);

gambar1 = figure;
plot(t,y,'color', [0 100 70]/255,'Linewidth',2)
axis([-5 5 -4.5 4.5])
xlabel('t')
ylabel('f(t)')