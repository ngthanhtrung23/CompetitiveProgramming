n=gets.to_i
s=gets.split''
puts ((0...n).map{|i| s[0...n].sort[i]<=>s[n...n+n].sort[i] }.reduce(:+).abs==n) ? :YES : :NO