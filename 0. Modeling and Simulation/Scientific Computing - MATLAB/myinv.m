function inv_A = myinv(A)
% Computes the inverse of a matrix
    X = A' / (norm(A,1) * norm(A,inf));
    while X * A ~= eye(size(A))
        X = X + X * (eye(size(A)) - A * X);
    end
    inv_A = X;
end
