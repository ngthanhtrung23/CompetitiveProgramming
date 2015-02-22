n=gets.to_i
a=gets.split.map(&:to_i)
gets.to_i.times {
  x,y=gets.split.map(&:to_i)
  a[x-2]+=y-1 if x>1
  a[x]+=a[x-1]-y if x<n
  a[x-1]=0
}
puts a
