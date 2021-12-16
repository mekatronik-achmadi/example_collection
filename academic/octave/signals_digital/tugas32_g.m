close all
clear
clc

t=-6:0.001:8;
t2=2*min(t):0.001:2*max(t);

x=3*(unit_step(t-1)-unit_step(t-2))+(unit_step(t-2)-unit_step(t-6));
h=unit_step(-2-t);

figure
subplot (2,1,1)
plot (t,x)

subplot (2,1,2)
plot (t,h)

y=conv(x,h);
figure
plot (t2,y,'color','r')
