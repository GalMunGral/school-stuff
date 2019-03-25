function primes = kraken(upperlimit)
    primes = [];
    i = 2;
    while i <= upperlimit
        if ~any(mod(i, primes) == 0)
            primes = [primes i];
        end
        i = i + 1;
    end
end

