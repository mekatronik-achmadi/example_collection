clear
clc
close all

t=-6:0.001:6;
A=2;
t0=5;

y=A*(unitstep(t+t0)-unitstep(t-t0));

figure(4)
plot(t,y,'color', [255 0 0]/255,'Linewidth',2)
axis([-6 6 0 3])