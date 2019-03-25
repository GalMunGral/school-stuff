function x = myltrisol(L)
% LTriSol subroutine
    [n, ~] = size(L);
    x = zeros(n,1);
    for j=1:n
        sol1 = (1 - L(j,1:j-1)*x(1:j-1)) / L(j,j);
        sol2 = (-1 - L(j,1:j-1)*x(1:j-1)) / L(j,j);
        if abs(sol1) >= abs(sol2)
            x(j) = sol1;
        else
            x(j) = sol2;
        end 
    end
end