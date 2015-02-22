n=gets.to_i;a=gets.split.map &:to_i
c=[0]*3
(0...n).each{|i|
  c[i%3] += a[i]
}
puts ["chest","biceps","back"][c.index(c.max)]
