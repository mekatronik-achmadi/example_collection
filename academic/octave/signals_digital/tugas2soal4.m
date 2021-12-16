clear
clc
close all

t=-5:0.4:5;
t0=1;

y=unitstep(-t+t0);

figure(1)
stem(t,y,'color', [0 0 0]/255,'Linewidth',2)
axis([-5 5 -1 2])
xlabel('n')
ylabel('f[n]')