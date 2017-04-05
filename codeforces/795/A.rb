input = gets.split.map &:to_i
n = input[0]
c1 = input[1]
c2 = input[2]

s = gets
adult = s.count '1'

res = 1000111000111000111
(1..adult).each do |group|
  bad = n % group
  good = group - bad
  x = n / group

  cur = good * (c1 + c2 * (x - 1) * (x - 1)) + bad * (c1 + c2 * x * x)

  if cur < res
    res = cur
  end
end
puts res
