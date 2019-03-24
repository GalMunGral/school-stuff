function [] = myplot(n)
% Compares how certain parameters affects the convergence rate.
    err1 = iteration1(n) - sqrt(2);
    err2 = iteration2(n) - sqrt(2);
    err3 = iteration3(n) - sqrt(2);
    k = linspace(1,n,n);
    plot(k,err1, 'r', k, err2, 'g', k, err3, 'b');
end

function x = iteration1(n)
    x = zeros(1,n);
    x(1) = 2;
    for i=2:n
        x(i) = x(i-1) - (x(i-1)^2-2)/(2*x(i-1));
    end
end

function x = iteration2(n)
    x = zeros(1,n);
    x(1) = 2;
    for i=2:n
        x(i) = x(i-1) - (x(i-1)^10-2^5)/(10*x(i-1)^9);
    end
end

function x = iteration3(n)
    x = zeros(1,n);
    x(1) = 2;
    for i=2:n
        x(i) = x(i-1) - (x(i-1)^20-2^10)/(20*x(i-1)^19);
    end
end
