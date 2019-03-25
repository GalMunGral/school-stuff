function [changes, minmax] = tierList(rankings)
changes = rankings(1:end-1) - rankings(2:end);
minIndex = find(rankings == min(rankings));
maxIndex = find(rankings == max(rankings));
minmax = [minIndex maxIndex];
end

