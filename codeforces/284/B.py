n = input()
a = raw_input()

cnti = 0
for i in xrange(n):
    if a[i] == 'I':
        cnti += 1

res = 0
for c in a:
    if c != 'F':
        otheri = cnti
        if c == 'I':
            otheri -= 1
        if otheri == 0:
            res += 1
print res
