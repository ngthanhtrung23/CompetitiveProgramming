i=[*$<]
n,k=i[0].split.map(&:to_i)
res=-10**9
(1..n).each{|j|
  f,t=i[j].split.map(&:to_i)
  res=[(t>k)?f-(t-k):f,res].max
}
p res
