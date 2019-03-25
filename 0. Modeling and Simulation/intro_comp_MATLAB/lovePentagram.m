function out = lovePentagram(comp1, comp2)
if strcmp(comp1, 'No-show')
    out = sprintf('%s''s opponent didn’t show up! Looks like MATLAB will choose him!', comp2);
    return
end
if strcmp(comp2, 'No-show')
    out = sprintf('%s''s opponent didn’t show up! Looks like MATLAB will choose him!', comp1);
    return
end
switch(comp1)
    case 'Chad'
        if strcmp(comp2,'Brad') || strcmp(comp2,'Kyle')
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp1, comp2);
        else
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp2, comp1);
        end
    case 'Brad'
        if strcmp(comp2,'Mike') || strcmp(comp2,'Kyle')
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp1, comp2);
        else
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp2, comp1);
        end
    case 'Drew'
        if strcmp(comp2,'Drew') || strcmp(comp2,'Chad')
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp1, comp2);
        else
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp2, comp1);
        end
    case 'Kyle'
        if strcmp(comp2,'Drew') || strcmp(comp2,'Mike')
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp1, comp2);
        else
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp2, comp1);
        end
    case 'Mike'
        if strcmp(comp2,'Brad') || strcmp(comp2,'Chad')
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp1, comp2);
        else
            out = sprintf('%s beats %s! He has proven his worth to MATLAB.', comp2, comp1);
        end
end

