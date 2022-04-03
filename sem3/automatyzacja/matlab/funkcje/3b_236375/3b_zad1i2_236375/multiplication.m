function [output] = multiplication(A,B)
if(nargin <= 1)
    error('Incorrect input size!');
else
    if(length(A) == 1 && length(B) > 1)
        [rowsB,colsB] = size(B);
        C = zeros(rowsB,colsB);
        for i = 1 : rowsB
            for j = 1 : colsB
                C(i,j) = A(1,1) * B(i,j);
            end
        end
        output = C;
    elseif(length(B) == 1 && length(A) > 1)
        [rowsA,colsA] = size(A);
        C = zeros(rowsA,colsA);
        for i = 1 : rowsA
            for j = 1 : colsA
                C(i,j) = A(i,j) * B(1,1);
            end
        end
        output = C;
    else
        [rowsA,colsA] = size(A);
        [rowsB,colsB] = size(B);
        if(colsA == rowsB && rowsA ~= colsB)
            C = zeros(rowsA,colsB);
            for i = 1 : rowsA
                for j = 1 : colsB
                    for k = 1 : colsA
                        C(i,j) = C(i,j) + A(i,k) * B(k,j);
                    end
                end
            end
        output = C;
        elseif(colsA == rowsB && rowsA == colsB)
            C = zeros(rowsA,colsB);
            for i = 1 : rowsA
                for j = 1 : colsB
                    for k = 1 : colsA
                        C(i,j) = C(i,j) + A(i,k) * B(k,j);
                    end
                end
             end
        output = C;
        else
            error('Incorrect input!');
        end
    end
end
end