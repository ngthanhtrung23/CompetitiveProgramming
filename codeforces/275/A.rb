a=Array.new(5){Array.new(5){1}}
(1..3).each{|i|
  x = gets.split.map(&:to_i).map{|x| x%2}
  (1..3).each{|j|
    if x[j-1] > 0
      a[i][j] ^= 1
      a[i-1][j] ^= 1
      a[i+1][j] ^= 1
      a[i][j-1] ^= 1
      a[i][j+1] ^= 1
    end
  }
}
(1..3).each{|i| puts a[i][1,3].join('')}
