function newStats = sportsStats(stats,cutoff)
stats(:, 6) = stats(:, 2) + stats(:, 3);
s = size(stats);
mask = false(1, s(1));
for i = 1:s(1)
    mask(i) = stats(i,5) <= cutoff;
end
stats = stats(mask, :);
stats(:, 4) = [];
stats = sortrows(stats, 1, 'descend');
s = size(stats);
mid = ceil(s(1) /2);
newStats = stats(1:mid, :);
end

