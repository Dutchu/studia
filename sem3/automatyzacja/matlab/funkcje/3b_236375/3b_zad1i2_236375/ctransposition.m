function [output] = ctransposition(A)
if(nargin < 1)
    error('Incorrect input size!');
else
    [rowsA,colsA] = size(A);
    B = zeros(colsA,rowsA);
    for i = 1 : rowsA
        for j = 1 : colsA
            if(isreal(A(i,j)))
                B(j,i) = A(i,j);
            else
                B(j,i) = conj(A(i,j));
            end
        end
    end
    output = B;
end