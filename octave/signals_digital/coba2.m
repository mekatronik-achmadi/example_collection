clear
clc
close all

t=-6:0.1:6;
A=2;
t0=5;

y=(-A*abs(t)/t0+A).*(unitstep(t+t0)-unitstep(t-t0));

figure(14)
plot(t,y,'color', [255 0 0]/255,'Linewidth',2)
axis([-6 6 0 3])