function out = ruleOfSeven(my_age,age_partner)
min_age = my_age/2 + 7;
if age_partner < 18
    out = 'This is illegal!';
elseif age_partner < min_age
    out = 'I''m gonna have to swipe left on you.';
else
    out = 'Love might just be in the air tonight!';
end
end
