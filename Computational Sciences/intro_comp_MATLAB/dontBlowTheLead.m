function newScores = dontBlowTheLead(scores)
s = size(scores);
mask = false(s(1), 1);
for i = 1:s(1)
    team = scores(i,:);
    a = (team(1) + team(2) + team(3)) == 28;
    b = (team(1) + team(2)) > (team(3) + team(4));
    mask(i) = ~a & ~b;
end
disp(mask)
newScores = scores(mask,:);
end

