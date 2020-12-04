# https://vietnam-national18.kattis.com/problems/joylessgame

ntest = int(raw_input())

FIRST = 'Chikapu'
SECOND = 'Bash'

for test in xrange(ntest):
    s = raw_input()
    n = len(s)

    if s[0] == s[-1]:
        if n % 2 == 0:
            print FIRST
        else:
            print SECOND
    else:
        if n % 2 == 0:
            print SECOND
        else:
            print FIRST
