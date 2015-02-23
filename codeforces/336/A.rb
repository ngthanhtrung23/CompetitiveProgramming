x,y=gets.split.map(&:to_i)
x1=y2=0;y1=x2=x.abs+y.abs
x2=-x2 if x<0
y1=-y1 if y<0
if x1>x2
  x1,x2=x2,x1
  y1,y2=y2,y1
end
puts "#{x1} #{y1} #{x2} #{y2}"
