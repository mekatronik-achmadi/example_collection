clear
clc
close all

t=-1:0.2:5;
t0=2;

y=unitstep(t-t0);

figure(1)
stem(t,y,'color', [0 160 70]/255,'Linewidth',2)
axis([-1 5 -1 1.5])
xlabel('n')
ylabel('f[n]')