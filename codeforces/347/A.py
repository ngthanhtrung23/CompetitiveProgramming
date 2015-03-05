n = input()
a = map(int, raw_input().split())

nn = min(a)
ln = max(a)
a.remove(nn)
a.remove(ln)
b = [ln]
b.extend(sorted(a))
b.append(nn)
print ' '.join(map(str, b))
