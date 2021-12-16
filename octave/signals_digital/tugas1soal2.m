clear
clc
close all

t=-5:0.001:5;
t0=3;

y=unitstep(t+t0);

figure(2)
plot(t,y,'color', [255 0 0]/255,'Linewidth',2)
axis([-5 5 -0.2 1.2])
xlabel('t')
ylabel('f(t)')