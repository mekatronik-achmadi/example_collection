function [rfs tx rx slen] = SceneParam()
% generate position vector based on tabel on page 45 on thesis.pdf

% transmitter part 
tx_x = [ 2.1; 49.1;  -1.2; -50.1];
tx_y = [51.0;  0.0; -50.0;   0.1];

tx = complex(tx_x,tx_y);

% receiver part
rx_x = [-51.5;-49.7;-30.5;-12.2;  9.8; 28.7; 44.3;46.6;49.1;52.4;35.8;10.5;-9.2;-27.0;-45.3;-49.2];
rx_y = [-10.7;-28.5;-49.1;-50.4;-49.6;-45.8;-37.2; -18;12.9;34.4;48.9;53.7;51.1; 47.8; 39.8; 17.5];
rx = complex(rx_x,rx_y);


% reflector part
rfs_x = [ 4.0;-20.0;-8.0];
rfs_y = [-3.0;-10.0;17.0];

rfs = complex(rfs_x,rfs_y);


% width of scene
slen = 70;

% make all unit to meter from centimeter
tx = tx/100;
rx = rx/100;
rfs = rfs/100;
slen = slen/100;

end

