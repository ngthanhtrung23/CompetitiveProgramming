# Algo: greedy
# - For each number, make it the smallest number which is greater than
#   previous number

ntest = int(raw_input())

def canSame(val, lb, ret):
    s_val = str(val)
    s_lb = str(lb)

    ret.append( len(s_lb) - len(s_val) )
    if len(s_lb) < len(s_val):
        return False

    if len(s_lb) == len(s_val):
        if val < lb:
            return False
        
        ret.append(val)
        return True

    greater = False
    for i in xrange(len(s_val)):
        if s_val[i] > s_lb[i]:
            greater = True
            break
        if s_lb[i] > s_val[i]:
            return False

    for i in xrange(len(s_val), len(s_lb)):
        if greater:
            s_val += '0'
        else:
            s_val += s_lb[i]

    ret.append(int(s_val))
    return True


def canPlus1(val, lb, ret):
    s_val = str(val)
    s_lb = str(lb)

    ret.append( len(s_lb) + 1 - len(s_val) )
    while len(s_val) < len(s_lb) + 1:
        s_val += '0'

    ret.append(int(s_val))
    return True


for test in xrange(1, ntest+1):
    n = int(raw_input())
    a = map(int, raw_input().split())
    assert len(a) == n

    res = 0
    for i in xrange(1, n):
        lb = int(a[i-1]) + 1

        ret = []
        if a[i] >= lb:
            pass
        elif canSame(a[i], lb, ret):
            res += ret[0]
            a[i] = ret[1]
        else:
            ret = []
            canPlus1(a[i], lb, ret)
            res += ret[0]
            a[i] = ret[1]

    # print a
    print("Case #{}: {}".format(test, res))
