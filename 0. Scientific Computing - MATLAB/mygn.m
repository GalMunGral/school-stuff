function x = mygn(t, y)
% Gauss-Newton method
    n = length(t);
    r = zeros(n,1);
    J = zeros(n,2);
    x = [1; 1];
    for k = 1:100
        % Construct residual and Jacobian
        for i = 1:n
            r(i) = y(i) - x(1) * exp(x(2) * t(i));
            J(i, 1) = -exp(x(2) * t(i));
            J(i, 2) = -x(1) * exp(x(2)* t(i)) * t(i);
        end
        % Calculate step size
        s = myls(J, -r);
        x = x + s;
    end         
end
