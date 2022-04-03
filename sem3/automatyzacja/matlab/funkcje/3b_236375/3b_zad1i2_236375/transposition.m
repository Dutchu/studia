function [output] = transposition(A)
if(nargin < 1)
    error('Incorrect input size!');
else
    [rowsA,colsA] = size(A);
    B = zeros(colsA,rowsA);
    for i = 1 : rowsA
        for j = 1 : colsA
            B(j,i) = A(i,j);
        end
    end
    output = B;
end