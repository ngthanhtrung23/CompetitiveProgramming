s = 0

def score(c)
  case c
  when 'Q'
    return 9
  when 'R'
    return 5
  when 'B'
    return 3
  when 'N'
    return 3
  when 'P'
    return 1
  else
    return 0
  end
end

8.times {
  gets.each_char { |c|
    if /[[:upper:]]/.match(c)
      s += score(c)
    elsif /[[:lower:]]/.match(c)
      s -= score(c.upcase)
    end
  }
}
if s > 0
  puts "White"
elsif s < 0
  puts "Black"
else
  puts "Draw"
end
