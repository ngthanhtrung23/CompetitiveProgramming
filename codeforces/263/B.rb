n, k = gets.split.map(&:to_i)
a = gets.split.map(&:to_i).sort
if k > n
  p -1
else
  print a[n-k],' ',a[n-k]
end
