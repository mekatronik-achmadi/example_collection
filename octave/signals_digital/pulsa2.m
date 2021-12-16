close all
clear
clc

t = -2:0.001:2;
y = pulsa(u(t+2)-u(t-2));

figure
plot(t,y)
axis([-2 2 -3.5 3.5])
grid on