function [updated, out] = brainless(monsters)
    mask = strcmpi(monsters, 'brainless');
    updated = monsters;
    updated(mask) = {'plants'};
    switch sum(sum(mask))
        case 0
            out = 'City clear. Move out!';
        case 1
            out = 'He didn''t stand a chance.';
        otherwise
            out = sprintf('Good work! We found %d zombies!', sum(sum(mask)));
    end
end
