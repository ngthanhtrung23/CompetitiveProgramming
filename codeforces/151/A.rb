a=gets.split.map &:to_i
n=a[0];p [a[5]/(n*a[7]),a[1]*a[2]/(n*a[6]),a[3]*a[4]/n].min
