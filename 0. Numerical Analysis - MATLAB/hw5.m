% My implementation of Gauss-Newton method
function x = my_gn(t, y)
  n = length(t);
  r = zeros(n,1);
  J = zeros(n,2);
  x = [1; 1];
  for k = 1:100
    for i = 1:n
      r(i) = y(i) - x(1) * exp(x(2) * t(i));
      J(i, 1) = -exp(x(2) * t(i));
      J(i, 2) = -x(1) * exp(x(2)* t(i)) * t(i);
    end
    s = myls(J, -r);
    x = x + s;
  end         
end

% Optimization with quadratic objective function, linear constraints
function [x, fval] = qlopt()
  result = fsolve(@qolc, rand(8,1));
  x = result(1:5);
  f = @(x) (4*x(1)-x(2))^2 + (x(2)+x(3)-2)^2 + (x(4)-1)^2 + (x(5)-1)^2;
  fval = f(x);
  disp("minimizer: ");
  disp(x);
  disp("value");
  disp(fval);
  
  function [c, ceq] = mycon(x)
    c = [];
    ceq = 1;
    ceq(1) = x(1)+3*x(2);
    ceq(2) = x(3)+x(4)-2*x(5);
    ceq(3) = x(2)-x(5);
  end

  [ex, efval] = fmincon(f,rand(5,1),[],[],[],[],[],[],@mycon);
  disp("expected:")
  disp(ex);
  disp("expected value:")
  disp(efval);
end

% Quadratic objective function, linear constraints
% Input x is an array of variables and multipliers;
% x(1) through x(5) are variables, x(6) through x(8) are multipliers
function F = qolc(x)
  grad = [
    2*(4*x(1)-x(2))*4;
    2*(4*x(1)-x(2))*(-1)+2*(x(2)+x(3)-2);
    2*(x(2)+x(3)-2);
    2*(x(4)-1);
    2*(x(5)-1)
  ];
  J = [
    1 3 0 0 0;
    0 0 1 1 -2;
    0 1 0 0 -1
  ];
  lambda = x(6:8);
  F(1:5) = grad + J'*lambda;
  F(6) = x(1)+3*x(2);
  F(7) = x(3)+x(4)-2*x(5);
  F(8) = x(2)-x(5);
end    


% Optimization with quadratic objective function & non-linear constraints
function [x, fval] = qnopt()
  result = fsolve(@qonc, rand(5,1));
  x = result(1:3);
  f = @(x) 4*x(1)^2 + 2*x(2)^2 + 2*x(3)^2 - 33*x(1) + 16*x(2) - 24*x(3);
  fval = f(x);
  disp("minimizer: ");
  disp(x);
  disp("value");
  disp(fval);
  
  function [c, ceq] = mycon(x)
    c = [];
    ceq(1) = 3*x(1)-2*x(2)^2-7;
    ceq(2) = 4*x(1)-x(3)^2-11;
  end
  
  [ex, efval] = fmincon(f,rand(3,1),[],[],[],[],[],[],@mycon);
  disp("expected:")
  disp(ex);
  disp("expected value:")
  disp(efval);
end

% Input x is an array of variables and multipliers;
% x(1) through x(3) are variables, x(4) through x(5) are multipliers
function F = qonc(x)
  grad = [
    4*2*x(1)-33;
    2*2*x(2)+16;
    2*2*x(3)-24
  ];
  J = [
    3 -2*2*x(2) 0;
    4 0 -1*2*x(3);
  ];
  lambda = x(4:5);
  F(1:3) = grad + J'*lambda;
  F(4) = 3*x(1)-2*x(2)^2-7;
  F(5) = 4*x(1)-x(3)^2-11;
end    


% Optimization with nonquadratic objective function & nonlinear constraints
function [x, fval] = nnopt()
  result = fsolve(@nonc, rand(8,1));
  x = result(1:5);
  f = @(x) (x(1)-1)^2 + (x(1)-x(2))^2 + (x(2)-x(3))^2 + (x(3)-x(4))^4 + (x(4)-x(5))^4;
  fval = f(x);
  disp("minimizer: ");
  disp(x);
  disp("value");
  disp(fval);
  
  function [c, ceq] = mycon(x)
    c = [];
    ceq = 1;
    ceq(1) = x(1)+x(2)^2+x(3)^3-3*sqrt(2)-2;
    ceq(2) = x(2)-x(3)^2+x(4)-2*sqrt(2)+2;
    ceq(3) = x(1)*x(5)-2;
  end
  
  [ex, efval] = fmincon(f,rand(5,1),[],[],[],[],[],[],@mycon);
  disp("expected:")
  disp(ex);
  disp("expected value:")
  disp(efval);
end

% Nonquadratic objective function, nonlinear constraints
% Input x is an array of variables and multipliers;
% x(1) through x(5) are variables, x(6) through x(8) are multipliers
function F = nonc(x)
  % Compute the gradient of the objective function
  grad = [
    2*(x(1)-1) + 2*(x(1)-x(2));
    2*(x(1)-x(2))*(-1) + 2*(x(2)-x(3));
    2*(x(2)-x(3))*(-1) + 4*(x(3)-x(4))^3;
    4*(x(3)-x(4))^3*(-1)+ 4*(x(4)-x(5))^3;
    4*(x(4)-x(5))^3*(-1)
  ];
  J = [
    1 2*x(2) 3*x(3)^2 0 0;
    0 1 -2*x(3) 1 0;
    x(5) 0 0 0 x(1)
  ];
  lambda = x(6:8);
  F(1:5) = grad + J'*lambda;
  F(6) = x(1)+x(2)^2+x(3)^3-3*sqrt(2)-2;
  F(7) = x(2)-x(3)^2+x(4)-2*sqrt(2)+2;
  F(8) = x(1)*x(5)-2;
end    


% Computes the extreme eigenvalues and corresponding eigenvectors of a matrix
% using a unconstrained optimization routine
function [k1, x1, k2, x2] = ueig(A)
  q = @(x) (x'*A*x) / (x'*x);
  nq = @(x) -(x'*A*x) / (x'*x);
  [x1, k1] = fminsearch(q, rand(length(A), 1));
  [x2, k2] = fminsearch(nq, rand(length(A), 1));
  k2 = -k2;
end

% Computes extreme eigenvalues using a constrained optimization routine
% to impose the constraint that the vector be normalized
function [k1, x1, k2, x2] = ceig(A)
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

% Solves the least-squares problem
function s = myls(A, b)
  disp(b);
  [Q1, R] = qr(A, 0);
  s = R \ (Q1' * b);
end

% Applies least-squares fitting to the logarithm of original function
function x = linear(t, y)
  A = zeros(length(t),2);
  b = arrayfun(@log,y);
  A(:,1) = 1;
  A(:,2) = t;
  s = myls(A, b);
  x = zeros(2,1);
  x(1) = exp(s(1));
  x(2) = s(2);
end
