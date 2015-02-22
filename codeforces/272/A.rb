n = gets.to_i
sum = gets.split.map(&:to_i).reduce(:+)
p (1..5).map{|i| ((i + sum) % (n+1) == 1) ? 0 : 1}.reduce(:+)
