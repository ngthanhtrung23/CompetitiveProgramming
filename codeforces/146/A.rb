n = gets.to_i
t = gets.chomp
s = t.split('').map(&:to_i)
puts (t=~/^(4|7)+$/ && s[0...n/2].sort == s[n/2...n].sort)?'YES':'NO'
