function battleFormation(numbers, filename)
f = fopen(filename, 'w');
width = max(numbers);
mid = (1 + width)/2;
for i = 1:length(numbers)
    line(1:width) = '0';
    d = (numbers(i)-1)/2;
    line(mid-d:mid+d) = '1';
    paddedLine = [line(1)];
    for j = 2:width
        paddedLine = [paddedLine '  ' line(j)];
    end
    fprintf(f, 'Line %d has the following line up: %s', i, paddedLine);
    if i ~= length(numbers)
        fprintf(f, '\n');
    end
end
fclose(f);
end

