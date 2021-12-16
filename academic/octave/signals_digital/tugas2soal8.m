clear
clc
close all

a=0.75
n=-2:0.2:3;
y=exp(a*n)

figure(5)
stem(n,y,'color',[200 40 10]/255,'Linewidth',2)
axis([-2 3 -4 10])
xlabel('n')
ylabel('f[n]')