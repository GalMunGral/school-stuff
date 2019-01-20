function cond = estcond2(A)
% Estimates conditional number using random matrices.
    cond = MyNorm(A) * EstInvNorm2(A);
end
