disp("Zad.1");

disp("a1");
a1 = [1,2,3; 4,5,6; 7,8,9];
disp(a1);

disp("a2");
a2 = [1,2,3
    4,5,6
    7,8,9];
disp(a2);

disp("a3");
a3 = [1:1:3; 4:1:6; 7:1:9];
disp(a3);

disp("a4");
x = 1;
for i = 1:3
    for j = 1:3
        A(i,j) = x;
        x = x + 1;
    end
end
disp(A);

