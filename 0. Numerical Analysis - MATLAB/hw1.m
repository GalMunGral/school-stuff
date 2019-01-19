% Finite difference
function d = fin_diff(f, x, h)
  d = (f(x+h) - f(x))/h;
end

% Error function for finite difference
function err = fd_err(h)
  expected = sec(1)^2;
  actual = fin_diff(@tan,1,h);
  err = abs(actual - expected);
end

% Tests finite difference routine
function [] = fd_test()
  x = logspace(0,-16,17);
  y = arrayfun(@fd_err, x);
  loglog(x,y);
  grid on;
end

% Central difference
function d = cen_diff(f, x, h)
  d = (f(x+h) - f(x-h)) / (2*h);
end

% Error function for central difference
function err = cd_err(h)
    expected = sec(1)^2;
    actual = cen_diff(@tan,1,h);
    err = abs(actual - expected);
end

% Tests central Difference
function [] = cd_test()
    x = logspace(0,-16,17);
    y = arrayfun(@cd_err, x);
    loglog(x,y);
    grid on;
end

% Generates Sequence
function seq = generate_seq(size)
  seq(1) = 1/3;
  seq(2) = 1/12;
  for i = 3:size
    seq(i) = 2.25 * seq(i-1) - 0.5 * seq(i-2);
  end
end

% Computes the exact value of the sequnce
function x = exact(k)
    x = 4^(1-k) / 3;
end

% Tests generate_seq routine 
function [] = gstest()
  correctseq = arrayfun(@exact, linspace(1,60,60));
  semilogy(correctseq);
  hold on;  
  seq = generate_seq(60);
  semilogy(seq);
  grid on;
end
