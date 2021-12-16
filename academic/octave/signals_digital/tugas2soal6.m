clear
clc
close all

t=-3:0.2:1;
t0=1;

y=delta(t+t0);

figure(5)
stem(t,y,'color',[20 0 0]/255,'Linewidth',2)
axis([-3 1 -1 2])
xlabel('n')
ylabel('f[n]')