function [output] = mexponentation(A,B)
if(nargin <= 1)
    error('Incorrect input size!');
else
    [rowsA,colsA] = size(A);
    [rowsB,~] = size(B);
    C = zeros(rowsB,colsA);
    for i = 1 : rowsA
        for j = 1: colsA
            C(i,j) = C(i,j) ^ B;
        end
    end
        output = C;
end
end
