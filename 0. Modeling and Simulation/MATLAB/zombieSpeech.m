% MATLAB
function zombieSpeech(file)
f = fopen(file);
line = fgetl(f);
map = containers.Map;

while ischar(line)
    [word, rest] = strtok(line, ' ');
    while ~isempty(word)
        if ~isKey(map, word)
            map(word) = 1;
        else
            map(word) = map(word) + 1;
        end
        [word, rest] = strtok(rest, ' ');
    end
    line = fgetl(f);
end

count = {};
count(:,1) = map.keys()';
count(:,2) = map.values()';
count = sortrows(count,1);
count = sortrows(count, 2, 'descend');

prefix = strtok(file, '.');
outFile = fopen([prefix '_counted.txt'], 'w');
[rows, ~] = size(count);
for i = 1:rows
    fprintf(outFile, '%s: %d\n', count{i,1}, count{i,2});
end
fclose(f);
fclose(outFile);
end
