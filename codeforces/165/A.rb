xs = Array.new(2011) { Array.new }
ys = Array.new(2011) { Array.new }

n = gets.to_i
a = []
Point = Struct.new(:x, :y)

(0...n).each { |i|
  x, y = gets.split.map(&:to_i)
  a << Point.new(x, y)
  xs[y+1000] << x
  ys[x+1000] << y
}
(0...2011).each { |i|
  xs[i].sort!
  ys[i].sort!
}

res = 0
a.each { |p|
  if xs[p.y+1000][0] < p.x && p.x < xs[p.y+1000][-1]
    if ys[p.x+1000][0] < p.y && p.y < ys[p.x+1000][-1]
      res += 1
    end
  end
}
p res
