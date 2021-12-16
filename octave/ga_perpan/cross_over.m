% Fungsi Elitism
function Child = cross_over(Parent1,Parent2)
    RandomValue = rand();
    Child(1) = RandomValue*Parent1 + (1- RandomValue)*Parent2;
    Child(2) = RandomValue*Parent2 + (1- RandomValue)*Parent1;
end