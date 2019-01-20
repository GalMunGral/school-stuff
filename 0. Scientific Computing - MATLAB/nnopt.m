function [x, fval] = nnopt()
% Optimization with nonquadratic objective function & nonlinear constraints
    result = fsolve(@nonc, rand(8,1));
    x = result(1:5);
    % The objective function
    f = @(x) (x(1)-1)^2 + (x(1)-x(2))^2 + (x(2)-x(3))^2 + (x(3)-x(4))^4 + (x(4)-x(5))^4;
    fval = f(x);
    disp("minimizer: ");
    disp(x);
    disp("value");
    disp(fval);
    % Compare with library routine
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

function F = nonc(x)
% Nonquadratic objective function, nonlinear constraints
% Input x is an array of variables and multipliers;
% x(1) through x(5) are variables, x(6) through x(8) are multipliers
    % Compute the gradient of the objective function
    grad = [
        2*(x(1)-1) + 2*(x(1)-x(2));
        2*(x(1)-x(2))*(-1) + 2*(x(2)-x(3));
        2*(x(2)-x(3))*(-1) + 4*(x(3)-x(4))^3;
        4*(x(3)-x(4))^3*(-1)+ 4*(x(4)-x(5))^3;
        4*(x(4)-x(5))^3*(-1)
    ];
    % Compute the Jacobian of the constraints
    J = [
        1 2*x(2) 3*x(3)^2 0 0;
        0 1 -2*x(3) 1 0;
        x(5) 0 0 0 x(1)
    ];
    % Get the multipliers
    lambda = x(6:8);
    % Feasibility
    F(1:5) = grad + J'*lambda;
    % Necessary conditions
    F(6) = x(1)+x(2)^2+x(3)^3-3*sqrt(2)-2;
    F(7) = x(2)-x(3)^2+x(4)-2*sqrt(2)+2;
    F(8) = x(1)*x(5)-2;
end    
