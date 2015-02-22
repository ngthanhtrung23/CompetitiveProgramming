n = gets.to_i
if n % 2 == 0
  (1..n/2).each { |i|
    print 2*i, ' ', 2*i-1, ' '
  }
else
  puts -1
end
