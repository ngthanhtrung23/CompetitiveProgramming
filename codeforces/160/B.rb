n = gets.to_i
s = gets.split('')
l = s[0...n].sort!
r = s[n...n+n].sort!
puts ((0...n).map{ |i| l[i] <=> r[i] }.reduce(:+).abs == n) ? "YES" : "NO"
