n, k = gets.split.map(&:to_i)
(1..k).each{|i| print n-i+1, ' '}
(1..(n-k)).each{|i| print i, ' '}
