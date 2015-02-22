n = gets.to_i
a = gets.split.map(&:to_i)
gets.to_i.times {
  x, y = gets.split.map(&:to_i)
  x -= 1
  if x > 0
    a[x-1] += y-1
  end
  if x < n-1
    a[x+1] += a[x] - y
  end
  a[x] = 0
}
a.each { |x| puts x }
