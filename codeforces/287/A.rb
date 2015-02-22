a=[*$<]
puts ([0,1,2].product([0,1,2]).map{|x,y|
  [x,x+1].product([y,y+1]).count{|u,v| a[u][v]=='#'}
} - [2]).empty? ? :NO : :YES