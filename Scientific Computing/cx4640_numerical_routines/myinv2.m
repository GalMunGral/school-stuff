function inv_A = myinv2(A)
% Computes the inverse of a matrix using Gaussian Elimination
    [n,~] = size(A);
    [L,U,piv] = gepiv(A);
    I = eye(n,n);
    P = I(piv,:);
    B = zeros(size(A));
    for i=1:n
        B(:,i) = ltrisol(L, P(:,i));
    end
    inv_A = zeros(size(A));
    for i=1:n
        inv_A(:,i) = utrisol(U,B(:,i));  
    end
end
