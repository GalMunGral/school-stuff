function n = estinvnorm1(A)
% Estimates the norm of the inverse of a matrix
% using my implementation of LTriSol subroutine
    [L,U] = lu(A);
    %First find y
    v = myltrisol(transpose(U));
    y = transpose(L)\v;
    %Use y to solve for z
    w = L\y;
    z = U\w;
    %Return the ratio
    n = norm(z,1) / norm(y,1);
end
