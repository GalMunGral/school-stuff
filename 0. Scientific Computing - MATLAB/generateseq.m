function seq = generateseq(size)
% Generates Sequence
    seq(1) = 1/3;
    seq(2) = 1/12;
    for i = 3:size
        seq(i) = 2.25 * seq(i-1) - 0.5 * seq(i-2);
    end
end
