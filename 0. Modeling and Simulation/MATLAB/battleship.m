function out = battleship(map1, map2, guesses)
step = 1;
while true
    [guess1, guesses] = strtok(guesses, ',');
    disp(guess1)
    row = str2double(guess1(2:end));
    column= double(guess1(1)) - 64;
    map2(row, column) = ' ';
    if all(map2 ~= 'O')
        out = sprintf('Player 1 won after %d turns.', step);
        return
    end
    [guess2, guesses] = strtok(guesses, ',');
    row = str2double(guess2(2:end));
    column= double(guess2(1)) - 64;
    map1(row, column) = ' ';
    if all(map1 ~= 'O')
        out = sprintf('Player 2 won after %d turns.', step);
        return
    end
    step = step + 1;
end
end

