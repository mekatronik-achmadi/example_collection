close all;clear;clc;

% add mfile path 
dir_mfile=fileparts(strcat(mfilename('fullpath'),'.m'));
addpath(dir_mfile);

% generate sound
[sound Fsamp]=GenerateS();

% generate position of Reflector,Transmitter, and Receiver
[Rfs Tx Rx SceLen]=SceneParam();

% simulate echo 
[sdat scdat]=SimulateEchos(Rfs,Tx,Rx,sound,Fsamp);

% implement backprojection to get final image
px_n = 100; %100x100
[pixg_res img_res] = Backproject(scdat, Tx, Rx, SceLen, px_n);

% show image result
bound = [-0.5,0.5,-0.5,0.5,0.5,0.5]; % [minX,maxX,minY,maxY,minZ,maxZ]
title = 'ini apa?';
cscale = [-20 1]; % min -20 dB max 1 db
ShowImage(img_res,bound,0.5,1,title,cscale);



