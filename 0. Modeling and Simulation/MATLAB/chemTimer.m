function [h2, m2] = chemTimer(h1, m1, m)
    time = h1 .* 60 + m1;
    time = mod((time + m), 12 * 60);
    h2 = floor(time./60);
    m2 = mod(time, 60);
end

