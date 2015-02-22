n = gets.to_i
s = gets.chomp.split('')
puts (s-['4','7']==[]&&s[0...n/2].sort==s[n/2...n].sort)?'YES':'NO'
