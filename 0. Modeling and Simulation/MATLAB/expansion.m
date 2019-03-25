function [v2] = expansion(p1,v1,p2)
    v2 = round(p1 .* v1 ./ p2, 2);
end

