function [] = cdtest()
% Tests central Difference
    x = logspace(0,-16,17);
    y = arrayfun(@cderr, x);
    loglog(x,y);
    grid on;
end

function err = cderr(h)
% Error function for central difference
    expected = sec(1)^2;
    actual = cendiff(@tan,1,h);
    err = abs(actual - expected);
end
