function [n] = stoichiometry(m, am)
    n = m ./ am .* 6.022e23;
end

