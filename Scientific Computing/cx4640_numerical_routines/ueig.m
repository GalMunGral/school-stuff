function [k1, x1, k2, x2] = ueig(A)
% Computes the extreme eigenvalues and corresponding eigenvectors of a matrix
% using a unconstrained optimization routine
% A: a matrix and starting vector

    % Create a function to compute Rayleigh quotient
    q = @(x) (x'*A*x) / (x'*x);
    % For computing maximum
    nq = @(x) -(x'*A*x) / (x'*x);
    % Compute the min eigenvalue/vector
    [x1, k1] = fminsearch(q, rand(length(A), 1));
    [x2, k2] = fminsearch(nq, rand(length(A), 1));
    k2 = -k2;
end
