close all
clear
clc

t = -2:0.01:2;
A = 2;
w = 2*pi*1;

y = A*sin(w*t+pi/2)
figure
plot(t,y,'bo-')
axis([-2 2 -2.5 2.5])

gambar = figure;
stem (t,y)

saveas(gambar,'cobagambar.jpg')