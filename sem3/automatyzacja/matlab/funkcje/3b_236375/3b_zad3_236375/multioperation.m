function [varargout] = multioperation(operation,varargin)
    ile_macierzy = length(varargin);
    if(ile_macierzy < 1)
        error('Incorrect input size!');
    end
    if(operation ~= "+" && operation ~= "*" && operation ~= ".*")
        error('Incorrect operation!')
    end
    ile_macierzy = length(varargin);
    potential_output = varargin{1};
    if(operation == "+")
        for i = 2 : ile_macierzy
            curr_size = size(varargin{i});
            if(curr_size == size(potential_output))
                potential_output = potential_output + varargin{i};
            end
        end
    elseif(operation == "*")
        [~,potential_outputCols] = size(potential_output);
        for i = 2 : ile_macierzy
            [inputRows,~] = size(varargin{i});
            if(potential_outputCols == inputRows)
                potential_output = potential_output * varargin{i};
            end
        end
    else
        for i = 2 : ile_macierzy
            curr_size = size(varargin{i});
            if curr_size == size(potential_output)
                potential_output = potential_output .* varargin{i};
            end
        end
    end
    varargout{1} = potential_output;
end

      