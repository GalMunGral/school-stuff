% MATLAB
function out = smashBallThief(a, b, c, d)
if ~any(xor(b,d)) & ~any(xor(b,c)) & ~any(xor(c,d))
    num = 1;
elseif ~any(xor(a,d)) & ~any(xor(a,c)) & ~any(xor(c,d))
    num = 2;
elseif ~any(xor(a,b)) & ~any(xor(a,d)) & ~any(xor(b,d))
    num = 3 ;
else
    num = 4;
end
out = sprintf('Suspect #%d stole the Smash Ball!', num);
end
