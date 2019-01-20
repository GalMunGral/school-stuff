function [] = fdtest()
% Tests finite difference routine
    x = logspace(0,-16,17);
    y = arrayfun(@fderr, x);
    loglog(x,y);
    grid on;
end

function err = fderr(h)
% Error function for finite difference
    expected = sec(1)^2;
    actual = findiff(@tan,1,h);
    err = abs(actual - expected);
end
