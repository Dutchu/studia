function [output] = mapow(a,b)

if(nargin < 2)
    error('Incorrect input');
end

[row_a,col_b] = size(a);
[row_b,~] = size(b);
result = zeros(row_b,col_b);

for i = 1 : row_a
    for j = 1: col_b
        result(i,j) = result(i,j) ^ b;
    end
end

output = result;

end

