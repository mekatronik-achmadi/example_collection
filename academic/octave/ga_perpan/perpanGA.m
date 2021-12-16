%% usual cleaning

close all;
clear;
clc;

%% paramater GA

% Mengatur Parameter Algoritma Genetika

% Jumlah individu dalam populasi
NIndividu = 100;
% Jumlah variabel dalam fungsi objektif
NVariant = 2;
% Maksimal Iterasi
NIteration = 300;
% Nilai Batas ,
% format Batas:
% { [Batas_Variabel_1;Batas_Variabel_2; Batas_Variabel_n] }
% Batas interval variabel 1 dan 2 [batas bawah,batas atas]
Bound = [0.01905,0.0254;35,55];
[Solution,Fitness] = geneticAlgorithm(NIndividu,NVariant,NIteration,Bound,@max,@objectFunctionGA);