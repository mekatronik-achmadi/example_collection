close all;clear;clc;

% add Spectral Projected Gradient for L1 minimization (SPGL1) libraries
dir_mfile=fileparts(strcat(mfilename('fullpath'),'.m'));
dir_spgl1=fullfile(dir_mfile,'spgl1-1.9');
addpath(dir_mfile);
addpath(dir_spgl1);

% generate sound
[sound Fsamp]=GenerateS();

% generate position of Reflector,Transmitter, and Receiver
[Rfs Tx Rx SceLen]=SceneParam();

% image parameters
imgparam.L=SceLen;
imgparam.N=100; %100x100

% create virtual data as observed data
delta = 0.001;
vRfs = Rfs-delta;
vTx = Tx-delta;
vRx = Rx-delta;

% generate sound
[sound Fsamp]=GenerateS();

% simulate echo both data
[Adat.data Acdat.data]=SimulateEchos(Rfs,Tx,Rx,sound,Fsamp);
[Ydat.data Ycdat.data]=SimulateEchos(vRfs,vTx,vRx,sound,Fsamp);

% generate data parameter for compressed sampling
nsample=100;
datparam=GenerateDataParam(Tx,Rx,nsample);

% run compressed sensing
nkeep = nsample*0.75; % sample yg diambil hanya 75% 
datparam.keepsamples = CompressedSensing(Tx,Rx,Acdat.data,nkeep);

% build compressed sensing parameter
[A Y] = MakeCSParameters(Acdat, Ycdat,datparam,imgparam,Fsamp);

% implement SPGL1 to get reconstruction
[x,r,g,info]=spg_bpdn(A,Y,1e-1);

% get final image
img_res = FormatCSImage(x,imgparam.N);

% show image result
bound = [-0.5,0.5,-0.5,0.5,0.5,0.5]; % [minX,maxX,minY,maxY,minZ,maxZ]
title = 'ini apa?';
cscale = [-20 1]; % min -20 dB max 1 db
ShowImage(img_res,bound,0.5,1,title,cscale);