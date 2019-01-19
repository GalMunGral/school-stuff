% Classical Gram–Schmidt method
function Q = classical_gs(A)
  [n,~] = size(A);
  Q = zeros(n);
  for i=1:n
    Q(:,i) = A(:,i);
    for j=1:i-1`
      r = Q(:,j)' * A(:,i);
      Q(:,i) = Q(:,i) - r*Q(:,j);
    end
    r = norm(Q(:,i),2);
    Q(:,i) = Q(:,i)/r; 
  end
end

% Classical Gram-Schmidt applied twice
function Q = classical_gs_x2(A)
  Q = classical_gs(classical_gs(A));
end

% Modified Gram-Schmidt method
function Q = modified_gs(A)
  [n,~] = size(A);
  Q = zeros(n);
  for i=1:n
    Q(:,i) = A(:,i);
    for j=1:i-1
      r = Q(:,j)' * Q(:,i);
      Q(:,i) = Q(:,i) - r*Q(:,j);
    end
    r = norm(Q(:,i),2);
    Q(:,i) = Q(:,i)/r; 
  end
end

% House holder method for comparison
function Q = householder(A)
  [Q, ~] = qr(A);
end

% A metric for the quality of factorization
function Y = quality(Q, N)
  Y = zeros(1,length(N));
  for i=1:length(N)
    n = N(i);
    H = hilb(n);
    Y(i) = -log10(norm(eye(n) - Q(H)'*Q(H), 2));
  end
end

% Plots the quality function of each method
function [] = my_plot_2()
  x = linspace(2,12,11);
  q1 = quality(@classical_gs, x);
  q2 = quality(@modified_gs, x);
  q3 = quality(@classical_gs_x2, x);
  q4 = quality(@householder, x);
  plot(x,q1,'r',x,q2,'g',x,q3,'b', x, q4, 'k');    
end
