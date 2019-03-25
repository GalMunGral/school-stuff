function out = seasonsOfLove(date1, date2)
[month1, date1] = strtok(date1);
date1 = str2double(strtok(date1));
[month2, date2] = strtok(date2);
date2 = str2double(strtok(date2));
season1 = month2season(month1, date1);
season2 = month2season(month2, date2);
if strcmp(season1, season2)
    out = sprintf('My crush and I were both born in %s. Now I''ll finally have a Valentine!', season1);
else
    out = sprintf('I''m a %s baby but my crush is a %s baby. At least I still have a date with MATLAB. #MatlabIsBae', season1, season2);
end

function season = month2season(month, day)
switch(month)
    case {'April', 'May'}
        season = 'Spring';
    case {'July', 'August'}
        season = 'Summer';
    case {'October', 'November'}
        season = 'Fall';
    case {'January', 'February'}
        season = 'Winter';
    case 'March'
        if day < 21
            season = 'Winter';
        else
            season = 'Spring';
        end
    case 'June'
        if day < 21
            season = 'Spring';
        else
            season = 'Summer';
        end
    case 'September'
        if day < 22
            season = 'Summer';
        else
            season = 'Fall';
        end
    case 'December'
        if day < 22
            season = 'Fall';
        else
            season = 'Winter';
        end
end
end
end