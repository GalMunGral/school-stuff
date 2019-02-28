function Q = classicalgsx2(A)
% Classical Gram-Schmidt applied twice
    Q = classicalgs(classicalgs(A));
end
