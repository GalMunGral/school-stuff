function out = kirbyCase(in)
remain = in;
out = '';
while (remain ~= "")
    [word, remain] = strtok(remain);
    word = lower(word);
    word = word(isletter(word));
    indices = strfind(word, 'kirby');
    if (~isempty(indices))
        word(indices(1): indices(1)+4) = 'KIRBY';
    end
    word(end) = upper(word(end));
    out = [out word];
end
end

