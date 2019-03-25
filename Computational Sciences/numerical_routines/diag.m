function D = diag(B)
% Diagonalizes a matirx
    b = (B(2,2) - B(1,1))/ B(1,2);
    r = roots([1, b, -1]);
    tan = r(1);
    c = 1 / norm([1 tan], 2);
    s = tan / norm([1 tan], 2);
    lRot = [c -s; s c];
    rRot = [c s; -s c];
    D = lRot * B * rRot;
end
