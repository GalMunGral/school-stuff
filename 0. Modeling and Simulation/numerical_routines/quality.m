function Y = quality(Q, N)
% A metric for the quality of factorization
    Y = zeros(1,length(N));
    for i=1:length(N)
        n = N(i);
        H = hilb(n);
        Y(i) = -log10(norm(eye(n) - Q(H)'*Q(H), 2));
    end
end
