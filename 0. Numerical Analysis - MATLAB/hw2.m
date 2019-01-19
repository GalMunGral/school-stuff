% My implementation of Gaussian Elimination with pivoting
function [L,U,piv] = ge_piv(A)
  [n,~] = size(A);
  piv = 1:n;
  for k=1:n-1
    [~,r] = max(abs(A(k:n,k)));
    q = r+k-1;
    piv([k q]) = piv([q k]);
    A([k q],:) = A([q k],:);
    if A(k,k) ~= 0
      A(k+1:n,k) = A(k+1:n,k)/A(k,k);
      A(k+1:n,k+1:n) = A(k+1:n,k+1:n) - A(k+1:n,k)*A(k,k+1:n);
    end
  end
  L = eye(n,n) + tril(A,-1);
  U = triu(A);
end

% Computes the inverse of a matrix using Gaussian Elimination
function AInv = MyInv(A)
  [n,~] = size(A);
  [L,U,piv] = GEPiv(A);
  I = eye(n,n);
  P = I(piv,:);
  B = zeros(size(A));
  for i=1:n
    B(:,i) = LTriSol(L, P(:,i));
  end
  AInv = zeros(size(A));
  for i=1:n
    AInv(:,i) = UTriSol(U,B(:,i));  
  end
end

% Helper method: Gets the diagonal of a matrix
function d = Diagonal(A)
  [n,~] = size(A);
  d = zeros(n,1);
  for i=1:n
    d(i) = A(i,i);
  end
end

% Tests the inverse computed from Gaussian Elimination
function [] = CreateTable()
  N = transpose(2:12);
  Relative_Error = zeros(11,1);
  Condition_Number = zeros(11,1);
  for n=2:12
    hilbM = hilb(n);
    computedInv = MyInv(hilbM);
    exactInv = invhilb(n);
    computedD = Diagonal(computedInv);
    exactD = Diagonal(exactInv);
    Relative_Error(n-1) = norm(computedD - exactD, 2) / norm(exactD, 2);
    Condition_Number(n-1) = cond(hilbM, 2);
  end
  T = table(N, Relative_Error, Condition_Number);
  T(:,:)
end

% Solves the nonsingular upper triangular system Ux = b
function x = UTriSol(U,b)
  n = length(b);
  x = zeros(n,1);
  for j=n:-1:2
    x(j) = b(j)/U(j,j);
    b(1:j-1) = b(1:j-1) - x(j)*U(1:j-1,j);
  end
  x(1) = b(1)/U(1,1);
end

% Solves the nonsingular lower triangular system Lx = b
function x = LTriSol(L,b)
  n = length(b);
  x = zeros(n,1);
  for j=1:n-1
    x(j) = b(j)/L(j,j);
    b(j+1:n) = b(j+1:n) - L(j+1:n,j)*x(j);
  end
  x(n) = b(n)/L(n,n);
end

% My implementation of LTriSol subroutine
function x = MyLTriSol(L)
  [n, ~] = size(L);
  x = zeros(n,1);
  for j=1:n
    sol1 = (1 - L(j,1:j-1)*x(1:j-1)) / L(j,j);
    sol2 = (-1 - L(j,1:j-1)*x(1:j-1)) / L(j,j);
    if abs(sol1) >= abs(sol2)
      x(j) = sol1;
    else
      x(j) = sol2;
    end 
  end
end

% Computes the infinite norm of a matrix for comparison
function norm = MyNorm(A)
  [~,n] = size(A);
  absColSums = zeros(1,n);
  for i=1:n
    absColSums(i) = sum(abs(A(:,i)));
  end
  norm = max(absColSums);
end

% Estimates the norm of the inverse of a matrix
% using my implementation of LTriSol subroutine
function n = EstInvNorm1(A)
  [L,U] = lu(A);
  v = MyLTriSol(transpose(U));
  y = transpose(L)\v;
  w = L\y;
  z = U\w;
  n = norm(z,1) / norm(y,1);
end

% Estimates condition number of a linear system
% using LU-factorization
function cond = EstCond1(A)
  cond = MyNorm(A) * EstInvNorm1(A);
end

% Estimates the norm of inverse using random matrices.
function n = EstInvNorm2(A)
  [m, ~] = size(A);
  norms = zeros(1,5);
  for i=1:5
    y = rand(m,1);
    z = A\y;
    norms(i) = norm(z,1) / norm(y,1);
  end
  n = max(norms);
end

% Estimates conditional number using random matrices.
function cond = EstCond2(A)
  cond = MyNorm(A) * EstInvNorm2(A);
end
