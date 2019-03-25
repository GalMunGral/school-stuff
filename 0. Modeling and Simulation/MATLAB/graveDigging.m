function [strength, immune] = graveDigging(in)
strength = 0;
immune = [];
for i = 1:length(in)
    value = getCellValue(in(i));
    strength = strength + value;
    if value == 0
        immune = [immune i];
    end
end
end

function value = getCellValue(cell)
if iscell(cell)
    value = getCellValue(cell{1});
else
    value = cell;
end
end