a,b=[*$<]
c=(a.to_i+b.to_i).to_s
a=a.tr('0','')
b=b.tr('0','')
c=c.tr('0','')
puts a.to_i+b.to_i==c.to_i ? :YES : :NO