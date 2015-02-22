cnt=[0]*6
a = $<.to_a[1].split.map(&:to_i)
a.each do |x|
  cnt[x] += 1
end
if cnt[5] >= 9 and cnt[0] > 0
  puts '5' * (cnt[5] - cnt[5] % 9) + '0' * cnt[0]
elsif cnt[0] > 0
  puts '0'
else
  puts '-1'
end
