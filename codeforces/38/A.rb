gets;a=gets.split.map(&:to_i)
x,y=gets.split.map(&:to_i)
res=0
while x < y do
  res += a[x-1]
  x += 1
end
p res
