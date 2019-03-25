function [c] = cosign(a, b, angle)
    l = sqrt(a.^2 + b.^2 - 2.*a.*b.*cos(angle.* pi./180));
    c = round(l, 3)
end

