n, k = gets.split.map(&:to_i)
p gets.split.map { |x|
  x.count('4') + x.count('7') <= k ? 1 : 0
}.reduce(:+)
