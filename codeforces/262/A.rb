n,k=gets.split.map(&:to_i)
p gets.split.map{|x| x.scan(/4|7/).size<=k ? 1 : 0}.reduce(:+)