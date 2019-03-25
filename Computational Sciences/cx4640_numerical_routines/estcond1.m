function cond = EstCond1(A)
% Estimates condition number of a linear system
% using LU-factorization
    cond = mynorm(A) * estinvnorm1(A);
end
