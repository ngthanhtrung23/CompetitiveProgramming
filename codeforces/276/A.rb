n,k=gets.split.map(&:to_i)
p (1..n).each.map{
  f,t=gets.split.map(&:to_i)
  (t>k)?f-(t-k):f
}.max
