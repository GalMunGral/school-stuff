function B = sym(A)
% Symmetrizes a matrix
    tan = (A(2,1) - A(1,2)) / (A(1,1) + A(2,2));
    c = 1 / norm([1 tan], 2);
    s = tan / norm([1 tan], 2);
    Rot = [c s; -s c];
    B = Rot * A;
end
