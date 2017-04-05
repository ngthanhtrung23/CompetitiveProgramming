var n, i : integer;
var s : ansistring;

begin
    readln(n);
    readln(s);
    
    for i := 1 to n do begin
      if (s[i] = 'a') or (s[i] = 'e') or (s[i] = 'i') or (s[i] = 'o') or (s[i] = 'u') or (s[i] = 'y') then begin
        if (i > 1) and (s[i] = s[i-1]) then begin
          if (s[i] = 'e') or (s[i] = 'o') then begin
            if (i = 2) or (s[i-2] <> s[i]) then begin
              if (i = n) or (s[i+1] <> s[i]) then begin
                write(s[i]);
              end
            end
          end
        end
        else begin
          write(s[i]);
        end
      end
      else write(s[i]);
    end
end.