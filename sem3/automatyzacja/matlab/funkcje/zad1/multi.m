function [output] = multi(a,b)

if(nargin < 2)
    error('Incorrect input');
end

[row_a,col_a] = size(a);
[row_b,col_b] = size(b);
result = zeros(row_a, col_b, row_b, col_b);

if(length(a) == 1 && length(b) > 1)


    for i = 1 : row_b
        for j = 1 : col_b
            result(i,j) = a(1,1) * b(i,j);
        end
    end
    output = result;
end

if(length(b) == 1 && length(a) > 1)


    for i = 1 : row_a
        for j = 1 : col_a
            result(i,j) = a(i,j) * b(1,1);
        end
    end
    output = result;
end


if(col_a == row_b && row_a ~= col_b)

    for i = 1 : row_a
        for j = 1 : col_b
            for k = 1 : col_a
                result(i,j) = result(i,j) + a(i,k) * b(k,j);
            end
        end
    end
    output = result;
end

if(col_a == row_b && row_a == col_b)

    for i = 1 : row_a
        for j = 1 : col_b
            for k = 1 : col_a
                result(i,j) = result(i,j) + a(i,k) * b(k,j);
            end
        end
    end
    output = result;
end

end
