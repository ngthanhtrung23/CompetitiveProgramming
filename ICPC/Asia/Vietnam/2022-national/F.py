#!/usr/bin/python3

ntest = int(input())
for test in range(ntest):
    name = input()
    first = input()
    last = input()
    print('YES' if name == last + first else 'NO')
