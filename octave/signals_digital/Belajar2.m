clear all
clear
clc

t1 = -10:0.1:-2;
t2 = -2:0.1:0;
t3 = 0:0.1:2;
t4 = -10:0.1:10;


y = sign(t1, t2, t3, t4);

figure
stem(t,y,'r*')
axis([-2 2 -1.5 1.5])
grid on