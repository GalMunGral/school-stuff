function out = hypePlays(names,comm)
[n1, names] = strtok(names, ',');
n2 = strtok(names, ',');
total = 20 * (strcmp(n1, 'Kirby') | strcmp(n2, 'Kirby')) -15 * (n1(1) == n2(1));
remain = comm;
while ~isequal(remain, '')
    [word, remain] = strtok(remain);
    total = total + 45 * strcmpi(word, 'finalsmash') + 10 * contains(word, n1) + 10 * contains(word, n2);
end
out = sprintf('The match between %s and %s received a score of %d points.', n1, n2, total);
end