function x = SolveForX(A,B,C,b)
    y = C\b;
    x = B\(2*A*y + 2*A*A*b + y + A*b);
end
