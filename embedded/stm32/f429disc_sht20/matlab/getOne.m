%% This script is used to get only one shot value

close all;
clear;
clc;

%% Define a serial device

devport = serial('/dev/ttyACM1',...
            'BaudRate',9600,...
            'DataBits',8,...
            'Parity','none',...
            'StopBits',1,...
            'Terminator','CR/LF');
        
devport.InputBufferSize = 1000000;
%% Try to get data
fopen(devport);

fprintf(devport,'test');
fprintf(devport,'test');
fprintf(devport,'test');

data = 0;
i = 1;
while(i<11)
    fprintf(devport,'sen');
    temp = str2double(fscanf(devport));
    if(isnan(temp))
        disp('value Nan');
    else
        disp("suhu: " + num2str(temp));
        data(i) = temp;
        i = i +1;
    end
    pause(1);
end

fclose(devport);
delete(devport);
clear devport;

%% Print Result
disp(data);

%% Try polyfit

x = 1:10;
poly_model = polyfit(x,data,3);

y = polyval(poly_model,x);
plot(x,y);
ylim([0 60]);
