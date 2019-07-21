function s = myls(A, b)
% Solves the least-squares problem
    disp(b);
    [Q1, R] = qr(A, 0);
    s = R \ (Q1' * b);
end
