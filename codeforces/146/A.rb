n = gets.to_i
t = gets
s = t.chomp.split(//).map(&:to_i)
puts (t=~/^(4|7)+$/ && s[0...n/2].reduce(:+) == s[n/2...n].reduce(:+))?'YES':'NO'
