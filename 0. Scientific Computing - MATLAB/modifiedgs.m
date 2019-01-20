function Q = modifiedgs(A)
% Modified Gram-Schmidt method
    [n,~] = size(A);
    Q = zeros(n);
    for i=1:n
        Q(:,i) = A(:,i);
        for j=1:i-1
            r = Q(:,j)' * Q(:,i);
            Q(:,i) = Q(:,i) - r*Q(:,j);
        end
        r = norm(Q(:,i),2);
        Q(:,i) = Q(:,i)/r; 
    end
end
