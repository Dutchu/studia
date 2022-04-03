function [varargout] = zad3b(varargin)
if(length(varargin) < 1)
    error('Incorrect input');
end
arg_num = length(varargin);
for i = 1 : arg_num
    if(isreal(varargin{i}))
        varargout{i} = varargin{i}.';
    else
        operations = {"'",".'"};
        operation = listdlg('PromptString','Wybierz typ transponowania','SelectionMode','single','ListString',operations);
        if(operation == 1)
            varargout{i} = varargin{i}';
        else
            varargout{i} = varargin{i}.';
        end
    end
end
for i = 1 : arg_num
    disp(varargout{i});
end
end