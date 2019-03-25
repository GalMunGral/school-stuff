function count = potOfGold(rainbow)
count = 0;
curRainbow = rainbow;
while ~isempty(curRainbow)
    count = count + curRainbow.gold;
    curRainbow = curRainbow.nextRainbow;
end
end

