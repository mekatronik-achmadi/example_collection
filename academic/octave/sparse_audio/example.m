% A practical example of sparse sampling

%Fs Hz (samples per second) is the rate at the speech signal is sampled
%Fs=2000;

% regular house keeping
close all;
clear;
clc;

%===============================================
% original and resampled

[x_ori,Fs_ori]=wavread('aris16.wav'); %read recording

% cut data to smaller processing
minValue = 135000;
maxValue = 150000; % ==> increment sampling 15000 (pendek aja bro) karena spectrum speech fluktuatif
x_o = x_ori(minValue:maxValue,1);
%sound(x_o,Fs_ori);

x = resample(x_o, 4000, 16000); % resample at different sample rate (why?)
Fs=8000; %what? ==> batas speech bit rate (64 bitrate dibagi 8 bit)
%sound(x,Fs);

figure(1)
stem(x, 'marker', 'none');
title('Recorded input speech signal');
xlabel('Length of the input speech signal');
ylabel('Amplitude of the input speech signal');

%===============================================
% Discrete cosine transform of the recorded signal

Fres = 1024;

%a0=dct(x); %unitary discrete cosine transform (why?)
a0=dct(x,Fres);
panjang=length(a0);

figure(2)
stem(a0)
axis([0 panjang -1 1]);
title('Discrete cosine transform of the recorded signal');
xlabel('Length of the DCT spectrum');
ylabel('Amplitude of the DCT spectrum');

%===============================================
% Thresholding the spectrum to make it sparse
% Centre clipping

a1=zeros(size(a0)); %create other matrix

for i=1:1:panjang;
    if a0(i,1)<=0.04 && a0(i,1)>=-0.06 % sparse by threshold?
        a1(i,1)=0;
    else
        a1(i,1)=a0(i,1); % hmm what?
    end
end

figure(3)
stem(a1)
axis([0 panjang -1 1]);
title('The Threshold spectrum');
xlabel('The length of the threshold spectrum');
ylabel('Amplitude of the threshold spectrum');

%===============================================
% Sparsity of the spectrum(K)and Length of the signal (N)
K=500;
N=panjang;

% Random measurement matrix
disp('Creating measurment matrix...');
A = randn(K,N); %what is this? ==> random gaussian normal
A = orth(A')'; % ==> cari eigen vector
figure(4)
imagesc(A)
colorbar;
colormap('lines');
title('Random Measurement matrix');
disp('Done.');

% observations vector
y = A*a1;
figure(5)
plot(y)
title('Observation Vector');

%initial guess = min energy
x0 = A'*y;

%===============================================
% solve the LP
tic
a2 = l1eqpd(x0, A, [], y, 1e-2); %Requested 78401x78401 (45.8GB) (whaaaattt??)
toc

figure(6)
stem(a2)
axis([0 panjang -0.6 0.6]);
title(' Reconstructed Spectrum using l1-minimization');
xlabel('The length of the reconstructed spectrum');
ylabel('Amplitude of the reconstructed spectrum');

%===============================================
% Inverse dicrete cosine transform of reconstructed signal (IDCT)
%Xrec=idct(xp);
Xrec=idct(a2,Fres);
%sound(Xrec,Fs);

figure(7)
stem(Xrec, 'marker', 'none');
title('Reconstructed signal');
xlabel('Length of the reconstructed signal using IDCT');
ylabel('Amplitude of the reconstructed signal using IDCT');

%===============================================
% Calculating Absolute error between the reconstructed and actual signal
% err=(max(abs(Xrec-x)));
% figure(8)
% stem(err);
% title(' Absolute Error of Reconstructed spectrum and Threshold spectrum ');
% xlabel('Length of the Maximum Absolute Error');
% ylabel('Maximum Absolute error')
