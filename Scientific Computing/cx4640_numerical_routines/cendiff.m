function d = cendiff(f, x, h)
% Central difference
    d = (f(x+h) - f(x-h)) / (2*h);
end
