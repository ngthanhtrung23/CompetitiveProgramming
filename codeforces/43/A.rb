c=Hash.new 0
[*$<].drop(1).each{|w| c[w] += 1}
puts c.max_by{|k,v| v}[0]