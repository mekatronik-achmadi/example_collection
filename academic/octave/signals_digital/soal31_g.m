close all
clear
clc

n = [-6;7];
x=[zeros(1,5) 1 1 0 1 1 zeros(1,4)];
h=[zeros(1,4) 1 2 3 2 1 zeros(1,5)];
y=conv(x,h);
n1=min(n*2):max(n*2);
stem(n1,y)

xlabel('n')
ylabel('y')
