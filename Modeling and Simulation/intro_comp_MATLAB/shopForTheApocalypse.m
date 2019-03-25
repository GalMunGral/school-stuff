function out = shopForTheApocalypse(list, inventory)
f = fopen(list);
line = fgets(f);
total = 0;
[~,~,data] = xlsread(inventory);
while ischar(line)
    [item, rest] = strtok(line, ' ');
    num = str2double(strtok(rest, ' '));
    rowMask = strcmpi(data(:,2), item);
    price = cell2mat(data(rowMask, 3));
    total = total + num * price;
    line = fgets(f);
end
out = sprintf('My total will be $%0.2f.', total);
fclose(f);
end