n,k=gets.split.map(&:to_i)
puts k>n ? -1 : "#{gets.split.map(&:to_i).sort[-k]} 0"
