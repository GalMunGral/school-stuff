function out = freShavocado(in)
remaining = in;
price = 0;
num = 0;
while  ~ isempty(remaining)
    [token, remaining] = strtok(remaining);
    if token(1) == '#'
        num = str2num(token(2:end));
    elseif token(1) == '$'
        price = str2num(token(2:end));
    end
end
out = sprintf('I need $%.2f to buy fresh avocados.', price .* num);
end

