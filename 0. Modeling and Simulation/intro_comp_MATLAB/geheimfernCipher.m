function geheimfernCipher(encodedFile, dictionary)
name = strtok(encodedFile, '.');
outFile = [name '_translated.txt'];
inFile = fopen(encodedFile);
outFile = fopen(outFile, 'w');
dictFile = fopen(dictionary);

% first create a dictionary
dictionary = containers.Map;
line = fgetl(dictFile);
while ischar(line)
    [key, rest] = strtok(line, '-');
    value = strtok(rest, '-');
    dictionary(key) = value;
    line = fgetl(dictFile);
end

line = fgets(inFile);
while ischar(line)
    newLine = '';
    [word, rest] = strtok(line);
    while ~isempty(word)
        newWord = dictionary(word);
        newLine = [newLine ' ' newWord];
        [word, rest] = strtok(rest);
    end
    newLine = [strtrim(newLine) '\n'];
    fprintf(outFile, newLine);
    line = fgets(inFile);
end
    

fclose(outFile);
fclose(dictFile);
fclose(inFile);
end

