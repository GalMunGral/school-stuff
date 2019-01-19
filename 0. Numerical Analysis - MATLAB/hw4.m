% Solves eigenproblem using Newton's method
function [x, lambda] = newton(A)
  [~, n] = size(A);
  x = rand(n,1);
  x = x/norm(x,2);
  lambda = x' * A * x;
  for i = 1:100
    % Iterative function
    F = zeros(n+1,1);
    F(1:n) = A * x - lambda * x;
    F(n+1) = x' * x - 1;
    % Jacobian
    J = zeros(n+1);
    J(1:n, 1:n) = A - lambda * eye(n);
    J(1:n, n+1) = -x;
    J(n+1, 1:n) = 2 * x';
    % Update x and lambda
    d = J \ (-F);
    x = x + d(1:n);
    lambda = lambda + d(n+1);
  end
end


% My implementation of Singular-value decomposition
function [U,S,V] = my_svd(A)
  tan = (A(2,1) - A(1,2)) / (A(1,1) + A(2,2));
  c = 1 / norm([1 tan], 2);
  s = tan / norm([1 tan], 2);
  Rot = [c s; -s c];
  B = Rot * A;
  b = (B(2,2) - B(1,1))/ B(1,2);
  r = roots([1, b, -1]);
  tan = r(1);
  c = 1 / norm([1 tan], 2);
  s = tan / norm([1 tan], 2);
  lRot = [c -s; s c];
  rRot = [c s; -s c];
  U = Rot' * lRot';
  S = lRot * B * rRot;
  V = rRot;
  for i = 1:2
    if S(i,i) < 0
      S(i,i) = - S(i,i);
      V(1:2,i) = - V(1:2,i);
    end
  end
end    

% Computes the inverse of a matrix
function InvA = my_inverse(A)
  X = A' / (norm(A,1) * norm(A,inf));
  while X * A ~= eye(size(A))
    X = X + X * (eye(size(A)) - A * X);
  end
  InvA = X;
end

% Computes inverse by LU-factorization
function InvA = lu_inverse(A)
  [L, U] = lu(A);
  W = L \ eye(size(A));
  InvA = U \ W;
end

% Compares two methods
function [] = Test()
  A = rand(5);
  InvA1 = my_inverse(A);
  InvA2 = lu_inverse(A);
  disp(InvA1);
  disp(InvA2);    
end

% Diagonalizes a matirx
function D = diagonalize(B)
  b = (B(2,2) - B(1,1))/ B(1,2);
  r = roots([1, b, -1]);
  tan = r(1);
  c = 1 / norm([1 tan], 2);
  s = tan / norm([1 tan], 2);
  lRot = [c -s; s c];
  rRot = [c s; -s c];
  D = lRot * B * rRot;
end

% Symmetrizes a matrix
function B = symmetrize(A)
  tan = (A(2,1) - A(1,2)) / (A(1,1) + A(2,2));
  c = 1 / norm([1 tan], 2);
  s = tan / norm([1 tan], 2);
  Rot = [c s; -s c];
  B = Rot * A;
end


% Compares how certain parameters affects the convergence rate.
function [] = my_plot(n)
  err1 = iteration_1(n) - sqrt(2);
  err2 = iteration_2(n) - sqrt(2);
  err3 = iteration_3(n) - sqrt(2);
  k = linspace(1,n,n);
  plot(k,err1, 'r', k, err2, 'g', k, err3, 'b');
end

function x = iteration_1(n)
  x = zeros(1,n);
  x(1) = 2;
  for i=2:n
    x(i) = x(i-1) - (x(i-1)^2-2)/(2*x(i-1));
  end
end

function x = iteration_2(n)
  x = zeros(1,n);
  x(1) = 2;
  for i=2:n
    x(i) = x(i-1) - (x(i-1)^10-2^5)/(10*x(i-1)^9);
  end
end

function x = iteration_3(n)
  x = zeros(1,n);
  x(1) = 2;
  for i=2:n
    x(i) = x(i-1) - (x(i-1)^20-2^10)/(20*x(i-1)^19);
  end
end
