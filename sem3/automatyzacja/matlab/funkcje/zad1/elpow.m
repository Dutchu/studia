function [output] = elpow(a,b)

if(nargin < 2)
    error('Incorrect input');
end

[row_a,col_a] = size(a);
[row_b,col_b] = size(b);
result = zeros(row_a,col_a);


if(row_a ~= col_a || row_b ~= 1 || col_b ~= 1)
    error('Incorrect input');
end



if(b(1,1) >= 2)

    for i = 1 : row_a
        for j = 1 : col_a
            for k = 1: b(1,1)
                result = multi(a,a);
            end
        end
    end

    output = result;

end

if(b(1,1) == 1)
    result = a;
    output = result;
end


end

