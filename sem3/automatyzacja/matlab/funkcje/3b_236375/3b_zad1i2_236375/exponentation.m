function [output] = exponentation(A,B)
if(nargin <= 1)
    error('Incorrect input size!');
else
    [rowsA,colsA] = size(A);
    [rowsB,colsB] = size(B);
    if(rowsA == colsA && rowsB == 1 && colsB == 1)
        C = zeros(rowsA,colsA);
        if(B(1,1) >= 2)
            for i = 1 : rowsA
                for j = 1 : colsA
                    for k = 1: B(1,1)
                        C = multiplication(A,A);
                    end
                end
            end
            output = C;
        elseif(B(1,1) == 1)
            C = A;
        output = C;
        end
    else
        error('Incorrect input!');
    end
end
end