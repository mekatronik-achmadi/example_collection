% https://www.mathworks.com/matlabcentral/newsreader/view_thread/33101

% bersihkan segala-galanya
close all
clc
clear all

% masukkan data ke memori
data_input;
data_output;

% tentukan jangkauan data
% dimulai dari 20 sehingga tidak perlu mengambil 20 nilai awal yang masih berantakan
jangkauan = (20:1450);

% parse (memisahkan) data untuk tiap variable input
u_11 = input_data(jangkauan,2); % input #1 di array ke 2
u_12 = input_data(jangkauan,4); % input #2 di array ke 4
u_13 = input_data(jangkauan,3); % input #3 di array ke 3

% parse (memisahkan) data untuk tiap variable output
y_11 = output_data(jangkauan,2); % output #1 di array ke 2
y_12 = output_data(jangkauan,3); % output #2 di array ke 3

% normalisasi nilai pada rentang 0 s/d 1
u11 = u_11/max(u_11);
u12 = u_12/max(u_12);
u13 = u_13/max(u_13);
y11 = y_11/max(y_11);
y12 = y_12/max(y_12);

% Plotting data
figure('Name','Input ter-Normalisasi','NumberTitle','off')
subplot(511),plot(u11);
grid;
legend('input #1');
subplot(512),plot(u12);
grid;
legend('input #2');
subplot(513),plot(u13);
grid;
legend('input #3');
subplot(514),plot(y11);
grid;
legend('output #1');
subplot(515),plot(y12);
grid;
legend('output #2');
