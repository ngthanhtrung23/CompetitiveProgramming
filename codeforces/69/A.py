s = [0, 0, 0]
n = input()
for i in xrange(n):
    t = map(int, raw_input().split())
    for j in xrange(3):
        s[j] += t[j]
print ('NO', 'YES')[s[0] == s[1] == s[2] == 0]
