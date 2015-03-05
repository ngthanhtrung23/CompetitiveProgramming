def g(s)
  case s
  when /lios$/
    return 1, 0
  when /liala$/
    return 1, 1
  when /etr$/
    return 2, 0
  when /etra$/
    return 2, 1
  when /initis$/
    return 3, 0
  when /inites$/
    return 3, 1
  else
    return -1, -1
  end
end

def v(words)
  return false if words.size==0
  return words[0][0] >= 0 if words.size==1
  l=-1
  c=0
  words.each { |w|
    return false if w[0]<0
    return false if w[1]!=words[0][1]
    c+=1 if w[0]==2
    return false if w[0]<l
    l=w[0]
  }
  return c == 1
end

words = gets.split
if v(words.map {|s| g(s) })
  puts 'YES'
else
  puts 'NO'
end
