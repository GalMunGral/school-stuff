function [count,out] = kingsSpeech(filename)
f = fopen(filename);
totalCount = 0;
count = 0;
line = fgetl(f);
while ischar(line)
    [word, rest] = strtok(line);
    while ~isempty(word)
        if strcmp(word, 'um') || strcmp(word, 'uh') || strcmp(word, 'like')
            count = count + 1;
        end
        totalCount = totalCount + 1;
        [word, rest] = strtok(rest);
    end
    line = fgetl(f);
end
fclose(f);
if count / totalCount < 0.02
    out = 'Wow what a good speech!';
elseif count / totalCount < 0.05
    out = 'Not bad, keep practicing.';
else
    out = 'Needs some work.';
end
end

