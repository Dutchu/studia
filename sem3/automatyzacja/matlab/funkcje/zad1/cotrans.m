function [output] = cotrans(a)

if(nargin < 1)
    error('Incorrect input');
end

[row_a,col_a] = size(a);
result = zeros(col_a, row_a);

for i = 1 : row_a
    for j = 1 : col_a
        if(isreal(a(i,j)))
            result(j,i) = a(i,j);
        else
            result(j,i) = conj(a(i,j));
        end
    end
end

output = result;

end