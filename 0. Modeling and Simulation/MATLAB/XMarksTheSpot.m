function out = XMarksTheSpot(map, directions)
path = map(1,1);
step = 1;
cur_i = 1;
cur_j = 1;
while map(cur_i, cur_j) ~= 'X' && step <= length(directions)
    dir = directions(step);
    step = step + 1;
    switch(dir)
        case 'N'
            cur_i = cur_i - 1;
        case 'S'
            cur_i = cur_i + 1;
        case 'W'
            cur_j = cur_j - 1;
        case 'E'
            cur_j = cur_j + 1;
    end
    path = [path map(cur_i, cur_j)];
end
if path(end) == 'X'
    out = sprintf('I found the treasure by following the path along %s!', path);
else
    out = sprintf('I went along the path %s but couldn''t find the treasure!', path);
end
end

