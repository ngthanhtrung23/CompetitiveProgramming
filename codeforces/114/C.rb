def get_info(s)
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

def verify(words)
  if words.size == 0
    return false
  end
  if words.size == 1
    return words[0][0] >= 0
  end
  last_type = -1
  count_noun = 0
  words.each { |word|
    # Must be valid word
    if word[0] < 0
      return false
    end
    # Must have same gender
    if word[1] != words[0][1]
      return false
    end
    # Must be increasing in type
    if word[0] == 2
      count_noun += 1
    end
    if word[0] < last_type
      return false
    end
    last_type = word[0]
  }
  return count_noun == 1
end

[*$<].each { |line|
  words = line.split
  if verify(words.map { |s| get_info(s) })
    puts 'YES'
  else
    puts 'NO'
  end
}

