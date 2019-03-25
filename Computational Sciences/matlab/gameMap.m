function [newMap,num] = gameMap(map, player, rows)
s = size(map);
mask = false(1,s(1));
for i = 1:length(rows)
    mask(rows(i)) = true;
end
mask = ~mask;
newMap = map(mask,:);

num = sum(sum(newMap == player));
end

