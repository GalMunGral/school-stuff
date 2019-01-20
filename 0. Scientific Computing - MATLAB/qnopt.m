function [x, fval] = qnopt()
% Optimization with quadratic objective function & non-linear constraints
    result = fsolve(@qonc, rand(5,1));
    x = result(1:3);
    % The objective function
    f = @(x) 4*x(1)^2 + 2*x(2)^2 + 2*x(3)^2 - 33*x(1) + 16*x(2) - 24*x(3);
    fval = f(x);
    disp("minimizer: ");
    disp(x);
    disp("value");
    disp(fval);
    % Compare with library routine
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

function F = qonc(x)
% Quadratic objective function, non-linear constraints
% Input x is an array of variables and multipliers;
% x(1) through x(3) are variables, x(4) through x(5) are multipliers
    % Compute the gradient of the objective function
    grad = [
        4*2*x(1)-33;
        2*2*x(2)+16;
        2*2*x(3)-24
    ];
    % Compute the Jacobian of the constraints
    J = [
        3 -2*2*x(2) 0;
        4 0 -1*2*x(3);
    ];
    % Get the multipliers
    lambda = x(4:5);
    % Feasibility
    F(1:3) = grad + J'*lambda;
    % Necessary conditions
    F(4) = 3*x(1)-2*x(2)^2-7;
    F(5) = 4*x(1)-x(3)^2-11;
end    
