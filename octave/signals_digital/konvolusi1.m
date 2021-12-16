close all
clear
clc

t=-10:0.001:10;
f=(-t+2).*(unit_step(t)-unit_step(t-2));
g=3*(unit_step(t+2)-unit_step(t-2));

figure
subplot (2,1,1)
plot (t,f)
axis([-4 4 0 4])

subplot (2,1,2)
plot (t,g)
axis([ -4 4 0 4])

[to yo]=konvolusi(f,g,t);
figure
plot (to,yo)
axis([ -4 6 0 7])