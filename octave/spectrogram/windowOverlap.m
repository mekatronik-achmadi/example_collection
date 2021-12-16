close all;
clear all;
clc;

%======================= Data Entry ======================
[y,Fs,bits]=wavread('Track 1_005.wav');
NFFT=256;

%======================= Overlap Setting ===================
nwin1=NFFT;
novr12=nwin1/2; % overlap 50%
novr14=nwin1/4; % overlap 25%
novr18=nwin1/8; % overlap 12.5%

nwin2=NFFT/2;
novr22=nwin2/2; % overlap 50%
novr24=nwin2/4;  % overlap 25%
novr28=nwin2/8; % overlap 12.5%

nwin4=NFFT/4;
novr42=nwin4/2; % overlap 50%
novr44=nwin4/4;  % overlap 25%
novr48=nwin4/8; % overlap 12.5%

nwin8=NFFT/8;
novr82=nwin8/2; % overlap 50%
novr84=nwin8/4;  % overlap 25%
novr88=nwin8/8; % overlap 12.5%

%======================= Calculate hamming Window Length ==================

win1=length(hamming(nwin1)); 
win2=length(hamming(nwin2)); 
win4=length(hamming(nwin4)); 
win8=length(hamming(nwin8)); 

%======================= Plot each overlap settings ===================
figure(1);
subplot(311);specgram(y,NFFT,Fs,hamming(nwin1),novr12);title(['hamming segment=' num2str(nwin1) ' overlap mount=' num2str(novr12)]);
subplot(312);specgram(y,NFFT,Fs,hamming(nwin1),novr14);title(['hamming segment=' num2str(nwin1) ' overlap mount=' num2str(novr14)]);
subplot(313);specgram(y,NFFT,Fs,hamming(nwin1),novr18);title(['hamming segment=' num2str(nwin1) ' overlap mount=' num2str(novr18)])

figure(2);
subplot(311);specgram(y,NFFT,Fs,hamming(nwin2),novr22);title(['hamming segment=' num2str(nwin2) ' overlap mount=' num2str(novr22)]);
subplot(312);specgram(y,NFFT,Fs,hamming(nwin2),novr24);title(['hamming segment=' num2str(nwin2) ' overlap mount=' num2str(novr24)]);
subplot(313);specgram(y,NFFT,Fs,hamming(nwin2),novr28);title(['hamming segment=' num2str(nwin2) ' overlap mount=' num2str(novr28)]);

figure(3);
subplot(311);specgram(y,NFFT,Fs,hamming(nwin4),novr42);title(['hamming segment=' num2str(nwin4) ' overlap mount=' num2str(novr42)]);
subplot(312);specgram(y,NFFT,Fs,hamming(nwin4),novr44);title(['hamming segment=' num2str(nwin4) ' overlap mount=' num2str(novr44)]);
subplot(313);specgram(y,NFFT,Fs,hamming(nwin4),novr48);title(['hamming segment=' num2str(nwin4) ' overlap mount=' num2str(novr48)]);

figure(4);
subplot(311);specgram(y,NFFT,Fs,hamming(nwin8),novr82);title(['hamming segment=' num2str(nwin8) ' overlap mount=' num2str(novr82)]);
subplot(312);specgram(y,NFFT,Fs,hamming(nwin8),novr84);title(['hamming segment=' num2str(nwin8) ' overlap mount=' num2str(novr84)]);
subplot(313);specgram(y,NFFT,Fs,hamming(nwin8),novr88);title(['hamming segment=' num2str(nwin8) ' overlap mount=' num2str(novr88)]);