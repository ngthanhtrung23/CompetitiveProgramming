s = gets.chomp
n = s.size
f = [0] * n
(1...n).each{|i|
  f[i] = ((s[i] == s[i-1])?1:0) + f[i-1]
}
gets.to_i.times {
  l, r = gets.split.map(&:to_i)
  puts f[r-1] - f[l-1]
}
