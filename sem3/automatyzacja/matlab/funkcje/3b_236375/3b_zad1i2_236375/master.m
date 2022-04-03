clear;
clc;
operations = {'+','*',"'",".'",'^','.^'};
operation = listdlg('PromptString','Select operation to perform.','SelectionMode','single','ListString',operations);
if(operation == 1)
    prompt = {'Enter first matrix.','Enter second matrix.'};
    dlgtitle = 'Addition';
    dims = [1 50];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        C = addition();
    elseif(isempty(answer{1}))
        if(isempty(answer{2}))
            C = addition();
        elseif(length(answer{2}) == 1)
            B = str2double(answer{2});
            C = addition(B);
        else
            B = str2num(answer{2});
            C = addition(B);
        end
    elseif(isempty(answer{2}) == 1)
        if(isempty(answer{1}) == 1)
            C = addition();
        elseif(length(answer{1}) == 1)
            A = str2double(answer{1});
            C = addition(A);
        else
            A = str2num(answer{1});
            C = addition(A);
        end
    else
        if(length(answer{1}) > 1 && length(answer{2}) == 1)
            A = str2num(answer{1});
            B = str2double(answer{2});
            opStart = tic;
            operatorVal = A + B;
            opStop = toc(opStart);
            mStart = tic;
            C = addition(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        elseif(length(answer{1}) == 1 && length(answer{2}) > 1)
            A = str2double(answer{1});
            B = str2num(answer{2});
            opStart = tic;
            operatorVal = A + B;
            opStop = toc(opStart);
            mStart = tic;
            C = addition(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        elseif(length(answer{1}) == 1 && length(answer{2}) == 1)
            A = str2double(answer{1});
            B = str2double(answer{2});
            opStart = tic;
            operatorVal = A + B;
            opStop = toc(opStart);
            mStart = tic;
            C = addition(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        else
           A = str2num(answer{1});
           B = str2num(answer{2});
           if(length(A) ~= length(B))
              C = addition(A,B);
           end
           opStart = tic;
           operatorVal = A + B;
           opStop = toc(opStart);
           mStart = tic;
           C = addition(A,B);
           mStop = toc(mStart);
           if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
           else
                error('Something gone wrong ...');
           end
           mFunctionTime = sprintf('M-function execution time: %f',mStop);
           opTime = sprintf('Built-in operator execution time: %f',opStop);
           disp(mFunctionTime);
           disp(opTime);
           disp('Result of operation:');
           disp(C);
        end
    end
elseif(operation == 2)
    prompt = {'Enter first matrix.','Enter second matrix.'};
    dlgtitle = 'Multiplication';
    dims = [1 50];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        C = multiplication();
    elseif(isempty(answer{1}))
        if(isempty(answer{2}))
            C = multiplication();
        elseif(length(answer{2}) == 1)
            B = str2double(answer{2});
            C = multiplication(B);
        else
            B = str2num(answer{2});
            C = multiplication(B);
        end
    elseif(isempty(answer{2}))
        if(isempty(answer{1}))
            C = addition();
        elseif(length(answer{1}) == 1)
            A = str2double(answer{1});
            C = multiplication(A);
        else
            A = str2num(answer{1});
            C = multiplication(A);
        end
    else
        if(length(answer{1}) > 1 && length(answer{2}) == 1)
            A = str2num(answer{1});
            B = str2double(answer{2});
            opStart = tic;
            operatorVal = A * B;
            opStop = toc(opStart);
            mStart = tic;
            C = multiplication(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        elseif(length(answer{1}) == 1 && length(answer{2}) > 1)
            A = str2double(answer{1});
            B = str2num(answer{2});
            opStart = tic;
            operatorVal = A * B;
            opStop = toc(opStart);
            mStart = tic;
            C = multiplication(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        elseif(length(answer{1}) == 1 && length(answer{2}) == 1)
            A = str2double(answer{1});
            B = str2double(answer{2});
            opStart = tic;
            operatorVal = A * B;
            opStop = toc(opStart);
            mStart = tic;
            C = multiplication(A,B);
            mStop = toc(mStart);
            if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
            else
                error('Something gone wrong ...');
            end
            mFunctionTime = sprintf('M-function execution time: %f',mStop);
            opTime = sprintf('Built-in operator execution time: %f',opStop);
            disp(mFunctionTime);
            disp(opTime);
            disp('Result of operation:');
            disp(C);
        else
           A = str2num(answer{1});
           B = str2num(answer{2});
           [rowsA,colsA] = size(A);
           [rowsB,colsB] = size(B);
           if(colsA ~= rowsB)
               C = multiplication(A,B);
           end
           opStart = tic;
           operatorVal = A * B;
           opStop = toc(opStart);
           mStart = tic;
           C = multiplication(A,B);
           mStop = toc(mStart);
           if(isequal(C,operatorVal))
                disp('Operations provided by m-function are correct!');
           else
                error('Something gone wrong ...');
           end
           mFunctionTime = sprintf('M-function execution time: %f',mStop);
           opTime = sprintf('Built-in operator execution time: %f',opStop);
           disp(mFunctionTime);
           disp(opTime);
           disp('Result of operation:');
           disp(C);
        end
    end
elseif(operation == 3)
    prompt = {'Enter matrix:'};
    dlgtitle = 'Complex conjugate transposition';
    dims = [1 55];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        B = ctransposition();
    elseif(length(answer{1}) > 1)
        A = str2num(answer{1});
        opStart = tic;
        operatorVal = A';
        opStop = toc(opStart);
        mStart = tic;
        B = ctransposition(A);
        mStop = toc(mStart);
        if(isequal(B,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(B);
    elseif(length(answer{1}) == 1)
        A = str2double(answer{1});
        opStart = tic;
        operatorVal = A';
        opStop = toc(opStart);
        mStart = tic;
        B = ctransposition(A);
        mStop = toc(mStart);
        if(isequal(B,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(B);
    else
        B = ctransposition();
    end
elseif(operation == 4)
    prompt = {'Enter matrix:'};
    dlgtitle = 'Transposition';
    dims = [1 50];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        B = transposition();
    elseif(length(answer{1}) > 1)
        A = str2num(answer{1});
        opStart = tic;
        operatorVal = A.';
        opStop = toc(opStart);
        mStart = tic;
        B = transposition(A);
        mStop = toc(mStart);
        if(isequal(B,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(B);
    elseif(length(answer{1}) == 1)
        A = str2double(answer{1});
        opStart = tic;
        operatorVal = A.';
        opStop = toc(opStart);
        mStart = tic;
        B = transposition(A);
        mStop = toc(mStart);
        if(isequal(B,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...\n');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(B);
    else
        B = transposition();
    end
elseif(operation == 5)
    prompt = {'Enter matrix:','Enter power:'};
    dlgtitle = 'Exponentation';
    dims = [1 50];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        C = exponentation();
    end
    if(isempty(answer{1}) || isempty(answer{2}))
        C = exponentation();
    elseif(isempty(answer{1}) && isempty(answer{2}))
        C = exponentation();
    else
        A = str2num(answer{1});
        B = str2double(answer{2});
        opStart = tic;
        operatorVal = A^B;
        opStop = toc(opStart);
        mStart = tic;
        C = exponentation(A,B);
        mStop = toc(mStart);
        if(isequal(C,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(C);
    end
else
    prompt = {'Enter matrix:','Enter power:'};
    dlgtitle = 'Element wise exponentation';
    dims = [1 50];
    answer = inputdlg(prompt,dlgtitle,dims);
    if(isempty(answer))
        C = exponentation();
    end
    if(isempty(answer{1}) || isempty(answer{2}))
        C = exponentation();
    elseif(isempty(answer{1}) && isempty(answer{2}))
        C = exponentation();
    else
        A = str2num(answer{1});
        B = str2num(answer{2});
        opStart = tic;
        operatorVal = A.^B;
        opStop = toc(opStart);
        mStart = tic;
        C = mexponentation(A,B);
        mStop = toc(mStart);
        if(isequal(C,operatorVal))
            disp('Operations provided by m-function are correct!');
        else
            error('Something gone wrong ...');
        end
        mFunctionTime = sprintf('M-function execution time: %f',mStop);
        opTime = sprintf('Built-in operator execution time: %f',opStop);
        disp(mFunctionTime);
        disp(opTime);
        disp('Result of operation:');
        disp(C);
    end
end
