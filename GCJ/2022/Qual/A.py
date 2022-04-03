ntest = int(input())


def cover(c):
    return '+-' * c + '+'

def cells(c):
    return '|.' * c + '|'


for test in range(ntest):
    print('Case #{}:'.format(test + 1))
    r, c = map(int, input().split())

    print('..' + cover(c-1))
    print('..' + cells(c-1))

    for i in range(r-1):
        print(cover(c))
        print(cells(c))

    print(cover(c))
