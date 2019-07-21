function ave_t = thisCanEmpty(ang, v)
    n = length(ang);
    total = 0;
    for i = 1:n
        vx = v(2*i - 1);
        vy = v(2*i);
        v0 = sqrt(vx.^2 + vy.^2);
        t = 2 .* v0 .* sin(ang(i)./180.*pi) ./ 9.8;
        total = total + t;
    end
    ave_t = round(total ./ n, 2);
end

