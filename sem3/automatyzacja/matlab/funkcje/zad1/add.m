function [output] = add(a,b)

if(nargin < 2)
    error('Incorrect input');
end

if(length(a) == 1)

    [row_b, col_b] = size(b);
    result = zeros(row_b, col_b);

    for i = 1 : row_b

        for j = 1 : col_b
            result(i,j) = a(1,1) + b(i,j);
        end

    end

    output = result;
end

if(length(b) == 1)

    [row_a,col_a] = size(a);
    result = zeros(row_a,col_a);

    for i = 1 : row_a

        for j = 1 : col_a
            result(i,j) = a(i,j) + b(1,1);
        end

    end

    output = result;
end

[row_a, col_a] = size(a);
[row_b, col_b] = size(b);

if(col_a == col_b && row_a == row_b)

    result = zeros(row_a,col_a);

    for i = 1 : row_a

        for j = 1 : col_a
            result(i,j) = a(i,j) + b(i,j);
        end

    end

    output = result;
end

end