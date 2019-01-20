function [U,S,V] = mysvd(A)
% Singular-value decomposition
    % Symmetrize
    tan = (A(2,1) - A(1,2)) / (A(1,1) + A(2,2));
    c = 1 / norm([1 tan], 2);
    s = tan / norm([1 tan], 2);
    Rot = [c s; -s c];
    % Diagonalize
    B = Rot * A;
    b = (B(2,2) - B(1,1))/ B(1,2);
    r = roots([1, b, -1]);
    tan = r(1);
    c = 1 / norm([1 tan], 2);
    s = tan / norm([1 tan], 2);
    lRot = [c -s; s c];
    rRot = [c s; -s c];
    % Combining two routines
    U = Rot' * lRot';
    S = lRot * B * rRot;
    V = rRot;
    % Correct the signs of singular values
    for i = 1:2
        if S(i,i) < 0
            S(i,i) = - S(i,i);
            V(1:2,i) = - V(1:2,i);
        end
    end
end
    