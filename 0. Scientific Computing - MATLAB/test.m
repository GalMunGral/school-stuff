function [] = test()
% Compares two methods
    A = rand(5);
    inv_A1 = myinv(A);
    inv_A2 = luinv(A);
    disp(inv_A1);
    disp(inv_A2);    
end

function inv_A = luinv(A)
% Computes inverse by LU-factorization
    [L, U] = lu(A);
    W = L \ eye(size(A));
    inv_A = U \ W;
end
