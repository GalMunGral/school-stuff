function [L,U,piv] = gepiv(A)
% My implementation of Gaussian Elimination with pivoting
    [n,~] = size(A);
    piv = 1:n;
    for k=1:n-1
        [~,r] = max(abs(A(k:n,k)));
        q = r+k-1;
        piv([k q]) = piv([q k]);
        A([k q],:) = A([q k],:);
        if A(k,k) ~= 0
            A(k+1:n,k) = A(k+1:n,k)/A(k,k);
            A(k+1:n,k+1:n) = A(k+1:n,k+1:n) - A(k+1:n,k)*A(k,k+1:n);
        end
    end
L = eye(n,n) + tril(A,-1);
U = triu(A);
