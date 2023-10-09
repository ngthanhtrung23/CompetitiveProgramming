#!/usr/bin/python3

from itertools import product


def pad(s, l):
    assert len(s) <= l
    return '0' * (l - len(s)) + s


ntest = int(input())

for test in range(ntest):
    left1, right1, left2, right2 = map(lambda x: str(bin(int(x)))[2:], input().split())

    maxlen = max(len(left1), len(right1), len(left2), len(right2))
    left1 = pad(left1, maxlen + 1)
    left2 = pad(left2, maxlen + 1)
    right1 = pad(right1, maxlen + 1)
    right2 = pad(right2, maxlen + 1)

    f = [[[[[0] * 2 for i1 in range(2)] for i2 in range(2)] for i3 in range(4)] for i4 in range(maxlen + 1)]
    for (ge1, le1, ge2, le2) in product([0, 1], [0, 1], [0, 1], [0, 1]):
        f[maxlen][ge1][le1][ge2][le2] = 1

    def add_one_digit(prefix_len, ge1, le1, ge2, le2, d1, d2):
        if (not ge1) and d1 < left1[prefix_len]:
            return None
        if (not le1) and d1 > right1[prefix_len]:
            return None
        if (not ge2) and d2 < left2[prefix_len]:
            return None
        if (not le2) and d2 > right2[prefix_len]:
            return None

        return (
            1 if d1 > left1[prefix_len] else ge1,
            1 if d1 < right1[prefix_len] else le1,
            1 if d2 > left2[prefix_len] else ge2,
            1 if d2 < right2[prefix_len] else le2,
        )

    for i in range(maxlen-1, -1, -1):
        for (ge1, le1, ge2, le2) in product([0, 1], [0, 1], [0, 1], [0, 1]):
            for d1 in '01':
                for d2 in '01':
                    key = add_one_digit(i+1, ge1, le1, ge2, le2, d1, d2)
                    if key is None:
                        continue

                    new_ge1, new_le1, new_ge2, new_le2 = key
                    f[i][ge1][le1][ge2][le2] += f[i+1][new_ge1][new_le1][new_ge2][new_le2]


    def cnt_prefix(prefix_len, prefix_inequalities):
        if len(prefix_inequalities) == 0:
            # No valid initial states
            return 0

        res = 0
        for ((ge1, le1, ge2, le2), weight) in prefix_inequalities.items():
            res += weight * f[prefix_len-1][ge1][le1][ge2][le2]
        return res

    def extend_prefix_one(prefix_len, prefix_inequalities, d1, d2):
        res = {}
        for ((ge1, le1, ge2, le2), weight) in prefix_inequalities.items():
            key = add_one_digit(prefix_len, ge1, le1, ge2, le2, d1, d2)
            if key is None:
                continue
            if key not in res:
                res[key] = weight
            else:
                res[key] += weight

        return res

    def extend_prefix(prefix_len, prefix_inequalities, options):
        res = {}
        for option in options:
            cur = extend_prefix_one(prefix_len, prefix_inequalities, option[0], option[1])
            for key, weight in cur.items():
                if key not in res:
                    res[key] = weight
                else:
                    res[key] += weight
        return res


    prefix_len = 1
    prefix_inequalities = {
        (0, 0, 0, 0): 1,
    }
    total = cnt_prefix(prefix_len, prefix_inequalities)
    k = (total + 1) // 2

    res = 0
    for i in range(1, maxlen+1):
        s1 = extend_prefix(prefix_len, prefix_inequalities, ['00', '11'])
        s2 = extend_prefix(prefix_len, prefix_inequalities, ['01', '10'])

        cur = cnt_prefix(prefix_len + 1, s1)
        if cur >= k:
            prefix_inequalities = s1
            prefix_len += 1
        else:
            res += 2 ** (maxlen - i)

            k -= cur
            prefix_inequalities = s2
            prefix_len += 1

    print(res)
