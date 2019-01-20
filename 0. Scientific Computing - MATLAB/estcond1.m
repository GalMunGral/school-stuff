function cond = EstCond1(A)
% Estimates condition number of a linear system
% using LU-factorization
    cond = MyNorm(A) * EstInvNorm1(A);
end
