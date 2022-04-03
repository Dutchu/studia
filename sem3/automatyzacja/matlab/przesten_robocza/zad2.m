
disp("complex B = ");
B = zeros(3,3);
x = 1;
for row = 1:3
    for col = 1:3
        B(row, col) = x + (x + 1)*1i;
        x = x + 1;
    end
end
disp(B);