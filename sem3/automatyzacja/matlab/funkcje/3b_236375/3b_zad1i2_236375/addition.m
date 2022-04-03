function [output] = add(a,b)

if(nargin < 2)
    error('Incorrect input');
end 

[row_a, clo_a] = size(a);
[row_b, clo_b] = size(b);

if(length(a) == 1)

    [row_b, clo_b] = size(b);
    c = zeros(row_b, clo_b);

    for i = 1 : row_b

        for j = 1 : clo_b
            c(i,j) = a(1,1) + b(i,j);
        end

    end

    output = c;

elseif(length(b) == 1)

    [row_a,clo_a] = size(a);
    c = zeros(row_a,clo_a);

    for i = 1 : row_a

        for j = 1 : clo_a
            c(i,j) = a(i,j) + b(1,1);
        end

    end

    output = c;

elseif(clo_a == clo_b && row_a == row_b)

    c = zeros(row_a,clo_a);

    for i = 1 : row_a

        for j = 1 : clo_a
            c(i,j) = a(i,j) + b(i,j);
        end

    end

    output = c;

end 

end