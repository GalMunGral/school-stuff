% MATLAB
function out = bachelor(age_height, info)
min_age = age_height(1);
max_height = age_height(2);
[name, info] = strtok(info, ',');
[age, info] = strtok(info, ',');
[height, info] = strtok(info, ',');
[foot, height] = strtok(height, '-');
inch = strtok(height, '-');
height = str2double(foot) + str2double(inch)/12;
[hometown, info] = strtok(info, ',');
[~, info] = strtok(info, ',');
[ability, ~] = strtok(info, ',');

if strcmp(name, 'Amanda')
    won = true;
elseif str2double(age) < min_age || height > max_height
    won = false;
elseif str2double(ability) > 7 || strcmp(hometown, 'Atlanta')
    won = true;
else
    won = false;
end
if won
    out = sprintf('%s will be on the next season of the Bachelor!', name);
else
    out = sprintf('Sorry, %s will have to find true love somewhere else.', name);    
end
end
