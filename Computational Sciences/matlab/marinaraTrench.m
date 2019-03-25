function [shallowest, deepest] = marinaraTrench(depth)
shallowest = realmax;
deepest = realmin;
[n,m] = size(depth);
for i = 1:n
    for j = 1:m
        if depth(i,j) < shallowest
            shallowest = depth(i,j);
        elseif depth(i,j) > deepest
            deepest = depth(i,j);
        end
    end
end
end

