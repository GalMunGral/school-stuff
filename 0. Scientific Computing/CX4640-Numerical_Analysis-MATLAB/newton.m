function [x, lambda] = newton(A)
% Solves eigenproblem using Newton's method
    [~, n] = size(A);
    x = rand(n,1);
    x = x/norm(x,2);
    lambda = x' * A * x;
    for i = 1:100
        % Iterative function
        F = zeros(n+1,1);
        F(1:n) = A * x - lambda * x;
        F(n+1) = x' * x - 1;
        % Jacobian
        J = zeros(n+1);
        J(1:n, 1:n) = A - lambda * eye(n);
        J(1:n, n+1) = -x;
        J(n+1, 1:n) = 2 * x';
        % Update x and lambda
        d = J \ (-F);
        x = x + d(1:n);
        lambda = lambda + d(n+1);
    end
end
