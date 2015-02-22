i=[*$<]
n, k = i[0].split.map(&:to_i)
def get(f, t, k)
  (t>k)?f-(t-k):f
end
res = -10**9
(1..n).each{|j|
  f, t = i[j].split.map(&:to_i)
  res = [get(f,t,k),res].max
}
p res
