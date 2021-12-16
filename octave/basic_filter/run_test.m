%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Written by Achmadi %%%%%%%%
%% For System Identification %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% close all windows then clear all variables and screen
close all
clear
clc

% load signal package (For Octave)
pkg load signal

% create bandpass filter bounds
c_freq = 500;
bw = 200;
[lcut,hcut] = f_bound(c_freq,bw);

% signal parameter
fs=2000; % sampling frequency
N=1024; % point amount
n=1:1:N; % point number
t=n/fs; % time variable

% generate sinusoidal signal
ys = sin((1000*pi*t)+(pi/6));

% generate random signal
% zero mean = 0 
% variance = 1
yn = randn(1,N);

% combine both signal
y = ys + yn;

% signal filter using bandpass
yf = bpfilter(y,fs,lcut,hcut);

% calculate all periodograms
[Pori,fori] = periodogram(ys,[],[],fs);
[Pbur,fbur] = periodogram(y,[],[],fs);
[Pfil,ffil] = periodogram(yf,[],[],fs);

% plot all signal
figure
subplot(3,1,1)
plot(t,ys)
ylim([-5 5])
ylabel('Original')
subplot(3,1,2)
plot(t,y)
ylim([-5 5])
ylabel('Noised')
subplot(3,1,3)
plot(t,yf)
ylim([-5 5])
ylabel('Filtered')
xlabel('Sample')
% print plot to file (Octave)
print -djpg signal.jpg

% plot all spectrograms
figure
subplot(3,1,1)
semilogy(fori,sqrt(Pori))
xlim([0 1000])
ylim([1e-2 1e1])
ylabel('Original')
subplot(3,1,2)
semilogy(fbur,sqrt(Pbur))
xlim([0 1000])
ylim([1e-2 1e1])
ylabel('Noised')
subplot(3,1,3)
semilogy(ffil,sqrt(Pfil))
xlim([0 1000])
ylim([1e-2 1e1])
ylabel('Filtered')
xlabel('Frequency')
% print plot to file (Octave)
print -djpg periodogram.jpg
