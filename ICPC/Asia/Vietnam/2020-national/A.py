n_test = int(raw_input())


def get(d, m):
    if m == 'Jan':
        if d <= 20:
            return 'Capricorn'
        else:
            return 'Aquarius'
    if m == 'Feb':
        if d <= 19:
            return 'Aquarius'
        else:
            return 'Pisces'
    if m == 'Mar':
        if d <= 20:
            return 'Pisces'
        else:
            return 'Aries'
    if m == 'Apr':
        if d <= 20:
            return 'Aries'
        else:
            return 'Taurus'
    if m == 'May':
        if d <= 20:
            return 'Taurus'
        else:
            return 'Gemini'
    if m == 'Jun':
        if d <= 21:
            return 'Gemini'
        else:
            return 'Cancer'
    if m == 'Jul':
        if d <= 22:
            return 'Cancer'
        else:
            return 'Leo'
    if m == 'Aug':
        if d <= 22:
            return 'Leo'
        else:
            return 'Virgo'
    if m == 'Sep':
        if d <= 21:
            return 'Virgo'
        else:
            return 'Libra'
    if m == 'Oct':
        if d <= 22:
            return 'Libra'
        else:
            return 'Scorpio'
    if m == 'Nov':
        if d <= 22:
            return 'Scorpio'
        else:
            return 'Sagittarius'
    if m == 'Dec':
        if d <= 21:
            return 'Sagittarius'
        else:
            return 'Capricorn'
    assert False


for test in xrange(n_test):
    d_str, month = raw_input().split()
    d = int(d_str)
    print get(int(d_str), month)
