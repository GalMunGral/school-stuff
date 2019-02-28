function x = linear(t, y)
% Applies least-squares fitting to the logarithm of original function
    A = zeros(length(t),2);
    b = arrayfun(@log,y);
    A(:,1) = 1;
    A(:,2) = t;
    s = myls(A, b);
    x = zeros(2,1);
    x(1) = exp(s(1));
    x(2) = s(2);
end
