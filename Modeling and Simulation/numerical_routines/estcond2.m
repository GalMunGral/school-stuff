function cond = estcond2(A)
% Estimates conditional number using random matrices.
    cond = mynorm(A) * estinvnorm2(A);
end
