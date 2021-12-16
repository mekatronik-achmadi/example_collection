close all
clear
clc

t = -2:0.01:2;
A = 4;
w = 2*pi*1;
y = A*sin(w*t+pi/2);

gambar1 = figure;
plot(t,y, '.')
axis([-2 2 -2.5 2.5])
grid on

gambar = figure;
stem(t,y, '.')
grid on;

%saveas(gambar,'amplitudo.png')
%saveas(gambar1,'amplitudo1.png')