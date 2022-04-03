function [output] = trans(a)

if(nargin < 1)
    error('Incorrect input');
end

[row_a,col_a] = size(a);
result = zeros(col_a, row_a);

for i = 1 : row_a
    for j = 1 : col_a
        result(j,i) = a(i,j);
    end
end

output = result;

end