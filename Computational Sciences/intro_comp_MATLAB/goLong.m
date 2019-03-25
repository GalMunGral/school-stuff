function [newField,distP, distR] = goLong(field)
s = size(field);
i = 1;
while isempty(find(field(i,:) == '*', 1))
    i = i + 1;
end
rowR = i;
colR = find(field(i,:) == '*');

for i = rowR:s(1)
    row = field(i,:);
    if ~isempty(find(row == 'Q',1))
        colQ = find(row == 'Q');
        rowQ = i;
    end
end
distP = round(sqrt((colQ - colR).^2 + (rowQ - rowR).^2),2);
countMatrix = field == '*';
distR = sum(countMatrix(:));
newField = field;
newField(rowR, colR) = 'W';
newField(field == 'W') = ' ';
end

