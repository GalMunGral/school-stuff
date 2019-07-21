function [k1, x1, k2, x2] = ceig(A)
% Computes extreme eigenvalues using a constrained optimization routine
% to impose the constraint that the vector be normalized
% A: a matrix and starting vector
    quotient = @(x) (x'*A*x)/(x'*x);
    nquotient = @(x) -(x'*A*x)/(x'*x);
    function [c, ceq] = mycon(x)
        c = 0;
        ceq = x'*x-1;
    end
    [x1, k1] = fmincon(quotient,rand(3,1),[],[],[],[],[],[],@mycon);
    [x2, k2] = fmincon(nquotient,rand(3,1),[],[],[],[],[],[],@mycon);
    k2 = -k2;
end
