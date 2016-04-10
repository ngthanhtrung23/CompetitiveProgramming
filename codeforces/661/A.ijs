print =: 1!:2&2
read =: 1!:1[3

in =. 2# ". (read-.LF)-.CR

nn =. */ in
n =. 0 { in

nnn =. n + nn

print 1 + nnn % 2