clear all;
clc;

%pengenalan fungsi XOR
disp('Metode Perceptron, Pengenalan fungsi XOR');
disp('Inisialisai : ');
thers = input('Nilai theta(thershold) : ');
alpha = input('Nilai Alpha(learning Rate) : ');
bobot(1) = input('Nilai awal bobot-1 : ');
bobot(2) = input('Nilai awal bobot-2 : ');
bobot(3) = input('Nilai awal bias : ');
x1 = [1 1 0 0];
x2 = [1 0 1 0];
t = [-1 1 1 -1];
format short;
for epoch = 1:100
    disp(['>>epoch-' num2str(epoch)]);
    fprintf('------------------------------------------------------------------------------------------\n');
    fprintf('  x1    x2    1    target    net     out          detla bobot                bobot\n');
    fprintf('------------------------------------------------------------------------------------------\n');
    for i = 1:4
        simpan = bobot;
        net(i) = bobot(3) + x1(i)*bobot(1) + x2(i)*bobot(2);
        out(i) = clasifi(net(i),thers);
        if ( out(i) == t(i) )
            bobot(1) = bobot(1);
            bobot(2) = bobot(2);
            bobot(3) = bobot(3);
        else
            bobot(1) = bobot(1) + alpha*t(i)*x1(i);
            bobot(2) = bobot(2) + alpha*t(i)*x2(i);
            bobot(3) = bobot(3) + alpha*t(i);
        end
        
        %delta bobot;
        for j = 1:3;
            delta_b(j) = bobot(j) - simpan(j);
        end
        fprintf(' %.1f   %.1f    1   %5.1f    %5.1f   %5.1f    %5.1f  %5.1f  %5.1f      %5.1f  %5.1f  %5.1f\n',x1(i),x2(i),t(i),net(i),out(i),...
                                                                                            delta_b(1),delta_b(2),delta_b(3),bobot(1),bobot(2),bobot(3));
    end
        fprintf('------------------------------------------------------------------------------------------\n\n');
end
         
 