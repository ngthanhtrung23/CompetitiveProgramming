n,k=gets.split.map &:to_i
p n.times.map{
  f,t=gets.split.map &:to_i
  (t>k)?f-(t-k):f
}.max
