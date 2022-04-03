function [varargout] = multitransposition(varargin)
if(length(varargin) < 1)
    error('Incorrect input size!');
else
    how_many = length(varargin);
    for i = 1 : how_many
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
    for i = 1 : how_many
        disp(varargout{i});
    end
end