function [] = gstest()
% Tests generate_seq routine 
    correctseq = arrayfun(@exact, linspace(1,60,60));
    semilogy(correctseq);
    hold on;
    seq = generateseq(60);
    semilogy(seq);
    grid on;
end

function x = exact(k)
% Computes the exact value of the sequnce
    x = 4^(1-k) / 3;
end
