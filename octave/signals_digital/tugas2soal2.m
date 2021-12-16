clear
clc
close all

t=-5:0.2:2;
t0=3;

y=unitstep(t+t0);

figure(1)
stem(t,y,'color', [0 0 100]/255,'Linewidth',2)
axis([-5 2 -1 1.5])
xlabel('n')
ylabel('f[n]')