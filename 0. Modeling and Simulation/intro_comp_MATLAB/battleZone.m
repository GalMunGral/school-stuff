function battleZone(filename, n)
map = [];
f = fopen(filename);
line = fgetl(f);
while ischar(line)
    map = [map; line];
    line = fgetl(f);
end
fclose(f);

for k=1:n
    [rows, cols] = size(map);
    tempMap = [];
    for i = 1:rows
        for j = 1:cols
            % Update cell
            switch map(i,j)
                case '.'
                    numCamp = countAdjacent(map, i, j, 'A');
                    if numCamp >= 1
                        tempMap(i,j) = 'i';
                    else
                        tempMap(i,j) = map(i,j);
                    end
                case 'i'
                    numSoldiers = countAdjacent(map, i, j, 'i');
                    if numSoldiers >= 2
                        tempMap(i,j) = 'A';
                    else
                        tempMap(i,j) = map(i,j); 
                    end
                case 'A'
                    numSoldiers = countAdjacent(map, i, j, 'i');
                    if numSoldiers < 2
                        tempMap(i,j) = '.';
                    else
                        tempMap(i,j) = map(i,j);
                    end
            end               
        end
    end
    map = tempMap;
end

name = strtok(filename, '.');
newFilename = [name '_updated.txt'];
f = fopen(newFilename, 'w');
for i = 1:rows-1
    fprintf(f, [map(i,:) '\n']);
end
fprintf(f, char(map(rows,:)));
fclose(f);
end


function count = countAdjacent(map, i, j, type)
[rows, cols] = size(map);
count = 0;
if i ~= 1 && map(i-1,j) == type
    count = count + 1;
end
if i ~= rows && map(i+1,j) == type
    count = count + 1;
end
if j ~= cols && map(i,j+1) == type
    count = count + 1;
end
if j ~= 1 && map(i, j-1) == type
    count = count + 1;
end
end
