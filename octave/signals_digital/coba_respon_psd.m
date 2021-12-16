num1=[20 15 15];
num2=[15 5];
denum=[200 450 350 225 125];
t= 0:0.1:100;
P=step(num1,denum,t);
plot(t,P),grid

Y=step(num2,denum,t);
plot(t,Y),grid