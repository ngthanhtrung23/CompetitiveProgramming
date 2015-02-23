students, subjects = gets.split.map(&:to_i)
a = []
students.times {
  a << gets.chomp.split('')
}
best = a.transpose.map(&:max)
res = 0
(0...students).each { |i|
  (0...subjects).each { |j|
    if a[i][j] == best[j]
      res += 1
      break
    end
  }
}
p res
