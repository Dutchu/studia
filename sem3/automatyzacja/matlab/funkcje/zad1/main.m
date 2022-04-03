clear;
clc;
prompt = "1 - +" + newline + "2 - *" + newline + "3 - '" + newline + "4 - .'" + newline + "5 - ^" + newline + "6 - .^" + newline +  "Waiting for input: ";
operation = input(prompt);
if(operation == 1)
    disp("Add"+ newline);

    disp("Enter first matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m1 = zeros(row, col);
    for i = 1 : row
        for j = 1 : col
            m1(i, j) = input("Enter the element: ");
        end
    end
    m1 = reshape(m1, [row,col]);
    disp(newline);
    disp("Enter second matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m2 = zeros(row,col);
    for i=1:row
        for j=1:col
            m2(i,j)=input("Enter the elements: ");
        end
    end
    m2 = reshape(m2, [row,col]);

    disp("Result: ");

    m_start = tic;
    disp(add(m1, m2));
    m_stop = toc(m_start);

    o_start = tic;
    result = m1 + m2;
    o_stop = toc(o_start);

    disp("Original operator result:");
    disp(result);

    disp("Original operator: " + o_stop + newline);
    disp("My operator function " + m_stop + newline);
    
end
if(operation == 2)
    disp("Multiplication"+ newline);

    disp("Enter first matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m1 = zeros(row, col);
    for i = 1 : row
        for j = 1 : col
            m1(i, j) = input("Enter the element: ");
        end
    end
    m1 = reshape(m1, [row,col]);
    disp(newline);
    disp("Enter second matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m2 = zeros(row,col);
    for i=1:row
        for j=1:col
            m2(i,j)=input("Enter the elements: ");
        end
    end
    m2 = reshape(m2, [row,col]);

    disp("Result: ");

    m_start = tic;
    disp(multi(m1, m2));
    m_stop = toc(m_start);

    o_start = tic;
    result = m1 * m2;
    o_stop = toc(o_start);

    disp("Original operator result:");
    disp(result);

    disp("Original operator: " + o_stop + newline);
    disp("My operator function " + m_stop + newline);
    
end
if(operation == 3)
    disp("Complex conjugate transpose"+ newline);

    disp("Enter matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m1 = zeros(row, col);
    for i = 1 : row
        for j = 1 : col
            m1(i, j) = input("Enter the element: ");
        end
    end
    m1 = reshape(m1, [row,col]);

    disp("Result: ");

    m_start = tic;
    disp(cotrans(m1));
    m_stop = toc(m_start);

    o_start = tic;
    result = m1';
    o_stop = toc(o_start);
    disp("Original operator result:");
    disp(result);

    disp("Original operator: " + o_stop + newline);
    disp("My operator function " + m_stop + newline);
    
end
if(operation == 4)
    disp("Transpose"+ newline);

    disp("Enter matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m1 = zeros(row, col);
    for i = 1 : row
        for j = 1 : col
            m1(i, j) = input("Enter the element: ");
        end
    end
    m1 = reshape(m1, [row,col]);

    disp("Result: ");

    m_start = tic;
    disp(trans(m1));
    m_stop = toc(m_start);

    o_start = tic;
    result = m1.';
    o_stop = toc(o_start);
    disp("Original operator result:");
    disp(result);

    disp("Original operator: " + o_stop + newline);
    disp("My operator function " + m_stop + newline);
       
end
if(operation == 5)
    disp("Matrix power"+ newline);

    disp("Enter first matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m1 = zeros(row, col);
    for i = 1 : row
        for j = 1 : col
            m1(i, j) = input("Enter the element: ");
        end
    end
    m1 = reshape(m1, [row,col]);
    disp(newline);
    disp("Enter second matrix");
    row = input("Enter the number of rows: ");
    col = input("Enter the number of coloumns: ");
    m2 = zeros(row,col);
    for i=1:row
        for j=1:col
            m2(i,j)=input("Enter the elements: ");
        end
    end
    m2 = reshape(m2, [row,col]);

    disp("Result: ");

    m_start = tic;
    disp(mapow(m1, m2));
    m_stop = toc(m_start);

    o_start = tic;
    result = m1 ^ m2;
    o_stop = toc(o_start);

    disp("Original operator result:");
    disp(result);

    disp("Original operator: " + o_stop + newline);
    disp("My operator function " + m_stop + newline);
    
end
if(operation == 6)
    disp('Element-wise power');
    a = input('Enter first matrix: ');
    b = input('Enter second matrix: ');
    disp(elpow(a, b));
end