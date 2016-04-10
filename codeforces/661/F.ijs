print =: 1!:2&2
read =: 1!:1[3

s =: (read-.CR)-.LF

in =. ". s

a =. 0 { in
b =. 1 { in


pi =: p:^:_1

res =. pi (b+1)
res =. res - (pi a)
print res