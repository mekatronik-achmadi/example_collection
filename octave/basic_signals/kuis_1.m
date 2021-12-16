close all;
clear all;
clc;

a = 3; 
T = 2; 
t = [0:0.001:1]'; 
y=a*mod(t,T); 
plot(t,y);