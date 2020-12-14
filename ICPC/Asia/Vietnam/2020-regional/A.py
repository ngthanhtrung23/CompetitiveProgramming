n_test = int(raw_input())


def xor_1_to_n(n):
    if n % 4 == 3:
        return 0
    if n % 4 == 0:
        return n
    if n % 4 == 1:
        return 1

    assert n % 4 == 2
    return n + 1


for test in xrange(n_test):
    n = int(raw_input())
    all = xor_1_to_n(n)
    if all == n:
        res = [i for i in xrange(1, n+1)]
    else:
        need = all ^ n
        assert need <= n
        res = [i for i in xrange(1, n+1) if i != need]

    sum_xor = 0
    for val in res:
        sum_xor = sum_xor ^ val
    assert sum_xor == n
    print len(res)
    print ' '.join([str(i) for i in res])

