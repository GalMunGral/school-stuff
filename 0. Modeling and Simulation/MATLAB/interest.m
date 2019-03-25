function [time] = interest(owed,rate,borrowed)
    t = log(owed./borrowed)./(rate./100);
    time = round(t, 2);
end

