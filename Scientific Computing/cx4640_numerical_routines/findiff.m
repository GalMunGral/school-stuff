function d = findiff(f, x, h)
% Finite difference
    d = (f(x+h) - f(x))/h;
end
