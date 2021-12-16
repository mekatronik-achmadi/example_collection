% Author: achmadi <achmadi@development>
% Created: 2018-09-03

close all 
clear
clc

% nilai koordinat dasar
% dari -v sampai v dengan interval i
v = 10;
i = 0.01;
t = -v:i:v;

% mulai gambar
figure(1)
hold on
axis('normal')

% buat persegi dengan 4 garis
% vertikal
plot(v*ones(size(t)), t ,'linewidth',4,'color',[0,0,0]);
plot(-v*ones(size(t)), t ,'linewidth',4,'color',[0,0,0]);
% horizontal
plot(t, v*ones(size(t)) ,'linewidth',4,'color',[0,0,0]);
area(t, v*ones(size(t)) ,'facecolor',[0,0,1]);
plot(t, -v*ones(size(t)) ,'linewidth',4,'color',[0,0,0]);
area(t, -v*ones(size(t)) ,'facecolor',[0,0,1]);

% formula lingkaran
% x = koordinat sejauh radius v 
% y = akardua( r^2 - x^2 )

% buat 1/4 lingkaran dengan pusat di pojok sisi kiri
xc = 0:i:v;
yc = sqrt(v^2 - xc.^ 2);
% atas
plot(xc-v, -(yc-v) ,'linewidth',4,'color',[0,0,0]);
area(xc-v, -(yc-v) ,'facecolor',[1,1,1]);
% bawah
plot(xc-v, yc-v ,'linewidth',4,'color',[0,0,0]);
area(xc-v, yc-v ,'facecolor',[1,1,1]);

% buat 1/4 lingkaran dengan pusat di pojok sisi kanan
xc = -v:i:0;
yc = sqrt(v^2 - xc.^ 2);
% atas
plot(xc+v, -(yc-v) ,'linewidth',4,'color',[0,0,0]);
area(xc+v, -(yc-v) ,'facecolor',[1,1,1]);
% bawah
plot(xc+v, yc-v ,'linewidth',4,'color',[0,0,0]);
area(xc+v, yc-v ,'facecolor',[1,1,1]);

% selesai gambar
hold off