n = [-2;20];
x=[zeros(1,2) ones(1,5) zeros(1,16)];
h=[zeros(1,4) ones(1,6) zeros(1,3) ones(1,6) zeros(1,4)];
y=conv(x,h);
n1=min(n*2):max(n*2);
stem(n1,y)

xlabel('n')
ylabel('y')
