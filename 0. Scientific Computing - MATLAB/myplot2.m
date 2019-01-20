function [] = myplot2()
% Plots the quality function of each method
    x = linspace(2,12,11);
    q1 = quality(@classicalgs, x);
    q2 = quality(@modifiedgs, x);
    q3 = quality(@classicalgsx2, x);
    plot(x,q1,'r',x,q2,'g',x,q3,'b');    
end
