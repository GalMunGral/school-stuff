function out = helpJaredLearnToRead(str, shift)
    len = length(str);
    mid = floor(len./2);
    out = blanks(len);
    str = lower(str);
    for i = 1:mid
        offset = double(str(i)) - 97;
        offset = mod(offset + shift, 26);
        out(i) = char(97 +offset);
    end
    for i = mid+1:len
        offset = double(str(i)) - 97;
        offset = mod(offset - shift, 26);
        out(i) = char(97 +offset);
    end    
end

