function d = diga2(A)
% Helper method: Gets the diagonal of a matrix
    [n,~] = size(A);
    d = zeros(n,1);
    for i=1:n
        d(i) = A(i,i);
    end
end
