function [] = createtable()
% Tests the inverse computed from Gaussian Elimination
    N = transpose(2:12);
    rel_err = zeros(11,1);
    cond_num = zeros(11,1);
    for n=2:12
        hilb_M = hilb(n);
        computed_inv = myinv2(hilb_M);
        exact_inv = invhilb(n);
        computed_D = diag2(computed_inv);
        exact_D = diag2(exact_inv);
        rel_err(n-1) = norm(computed_D - exact_D, 2) / norm(exact_D, 2);
        cond_num(n-1) = cond(hilb_M, 2);
    end
    T = table(N, rel_err, cond_num);
    T(:,:)
end
