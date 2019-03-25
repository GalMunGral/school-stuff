function [vol] = frustum(h, r1, r2)
    vol = round(1/3 .* pi .* (r1.^2 + r2.^2 + r1.*r2).* h, 2);
end

