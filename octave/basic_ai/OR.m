clear all;
clc;

%pengenalan fungsi OR
ftulis = fopen('JST_OR_PRECEPTRON(MATLAB).txt','w');
disp('Metode Perceptron, Pengenalan fungsi OR');
fprintf(ftulis,'Metode Perceptron, Pengenalan fungsi OR\n');
disp('Inisialisai : ');
fprintf(ftulis,'Inisialisai : \n');
thers = input('Nilai theta(thershold) : ');
alpha = input('Nilai Alpha(learning Rate) : ');
bobot(1) = input('Nilai awal bobot-1 : ');
bobot(2) = input('Nilai awal bobot-2 : ');
bobot(3) = input('Nilai awal bias : ');

fprintf(ftulis,'Nilai tetha(threshold) : %f\n', thers);
fprintf(ftulis,'Nilai Alpha(learning Rate) : %f\n', alpha);
fprintf(ftulis,'Nilai awal bobot-1 : %f\n', bobot(1));
fprintf(ftulis,'Nilai awal bobot-2 : %f\n', bobot(2));
fprintf(ftulis,'Nilai awal bobot-3 : %f\n', bobot(3));

x1 = [1 1 0 0];
x2 = [1 0 1 0];
t = [1 1 1 -1];
format short;
for epoch = 1:12
    
    fprintf(ftulis,'>>epoch-%d\n', epoch);
    fprintf(ftulis,'\n');
    fprintf(ftulis,'------------------------------------------------------------------------------------------');
    fprintf(ftulis,'\n');
    fprintf(ftulis,'  x1    x2    1    target    net     out          detla bobot                bobot\n');
    fprintf(ftulis,'\n');
    fprintf(ftulis,'------------------------------------------------------------------------------------------\n');
    
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
        fprintf(ftulis,' %.1f   %.1f    1   %5.1f    %5.1f   %5.1f    %5.1f  %5.1f  %5.1f      %5.1f  %5.1f  %5.1f\n',x1(i),x2(i),t(i),net(i),out(i),...
                                                                                            delta_b(1),delta_b(2),delta_b(3),bobot(1),bobot(2),bobot(3));
        
        fprintf(' %.1f   %.1f    1   %5.1f    %5.1f   %5.1f    %5.1f  %5.1f  %5.1f      %5.1f  %5.1f  %5.1f\n',x1(i),x2(i),t(i),net(i),out(i),...
                                                                                            delta_b(1),delta_b(2),delta_b(3),bobot(1),bobot(2),bobot(3));
    end
        fprintf(ftulis,'------------------------------------------------------------------------------------------\n\n');
        fprintf('------------------------------------------------------------------------------------------\n\n');
end
fclose(ftulis);
edit JST_OR_PRECEPTRON(MATLAB).txt;   
         
 