function [buffedCharacters, damageModified] = rage(characters, rageVec, damage)
n = length(rageVec);
chs = strsplit(characters);
buffedCharacters=strjoin(chs(rageVec));
damageModified(rageVec) = round(damage(rageVec) * 1.15, 1);
damageModified(~rageVec) = damage(~rageVec);
end

