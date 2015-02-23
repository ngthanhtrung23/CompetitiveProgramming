gets;a=gets.split.map(&:to_i)
p a.map{|x| 1-(a.reduce(:+)-x)%2}.reduce(:+)