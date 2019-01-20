function norm = mynorm(A)
% Computes the infinite norm of a matrix for comparison
    [~,n] = size(A);
    abs_col_sums = zeros(1,n);
    for i=1:n
        abs_col_sums(i) = sum(abs(A(:,i)));
    end
    norm = max(abs_col_sums);
end
        