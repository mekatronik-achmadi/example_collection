clear
clc
close all

t = -6:0.1:6;
A = 2;
to = 5;

y = (-A * abs(t) / to + A).*(unitstep(t+to)-unitstep(t-to));


figure(1)
plot(t,y,'color',[10 100 75]/255,'Linewidth',5)
axis([-6 6 0 3])