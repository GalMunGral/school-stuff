function out = sportsBall(in, word, chr)
r = blanks(length(word));
r(:) = chr;
s = size(in);
in = reshape(strrep(reshape(in,1,[]), word, r), s(1), s(2));
in = in(end:-1:1,:);
in = reshape(strrep(reshape(in,1,[]), word, r), s(1), s(2));
in = in(end:-1:1,:);
in = in';
in = reshape(strrep(reshape(in,1,[]), word, r), s(2), s(1));
in = in';
in = in';
in = in(end:-1:1, :);
in = reshape(strrep(reshape(in,1,[]), word, r), s(2), s(1));
in = in(end:-1:1, :);
out = in';
end

