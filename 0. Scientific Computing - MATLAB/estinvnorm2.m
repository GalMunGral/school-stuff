function n = estinvnorm2(A)
% Estimates the norm of inverse using random matrices.
    [m, ~] = size(A);
    norms = zeros(1,5);
    for i=1:5
        y = rand(m,1);
        z = A\y;
        norms(i) = norm(z,1) / norm(y,1);
    end
    n = max(norms);
end
