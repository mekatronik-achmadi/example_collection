close all
clear
clc

t=-4:0.001:4;
t2=2*min(t):0.001:2*max(t);

x=delta(t)-2*delta(t-1)+delta(t-2);
h=(unit_step(t)-unit_step(t-1))+2*(unit_step(t-1)-unit_step(t-2));

figure
subplot (2,1,1)
stem (t,x,'.')

subplot (2,1,2)
plot (t,h)

y=conv(x,h);
figure
plot (t2,y,'color','r')
