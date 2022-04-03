
function [varargout] = zad3a(operation,varargin)

if(operation ~= "+" && operation ~= "*" && operation ~= ".*")
    error('Incorrect input')
end

arg_num = length(varargin);
disp(operation);z

result = 0;

if(operation == "+")
    for i = 1 : arg_num
        result = result + varargin{i};
    end
end

if(operation == "*")
    result = 1;
    for i = 1 : arg_num
        result = result * varargin{i};
    end
end

if(operation == ".*")
    result = 1;
    for i = 1 : arg_num
        result = result .* varargin{i};
    end
end

disp(result);
end

