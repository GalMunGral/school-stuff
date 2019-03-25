function [mineCount, dangerLevel] = minefield(filename)
mineCount = 0;
f = fopen(filename);
line = fgets(f);
while ischar(line)
    mineCount = mineCount + sum(line == '*');
    line = fgets(f);
end
if mineCount < 5
    dangerLevel = 'This beach seems like a good landing spot!';
else
    dangerLevel = 'We can not risk our soldiers here!';
end
fclose(f);
end
