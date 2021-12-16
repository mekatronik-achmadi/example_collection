close all
clear
clc

n = [-7;7];
x=[zeros(1,5) 1 2 1 1 zeros(1,6)];
h=[zeros(1,7) 1 -1 0 0 1 1 zeros(1,2)];
y=conv(x,h);
n1=min(n*2):max(n*2);
stem(n1,y)

xlabel('n')
ylabel('y')
