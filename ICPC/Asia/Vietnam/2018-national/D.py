# https://vietnam-national18.kattis.com/problems/dreamer

import datetime
import itertools

ntest = int(raw_input())

# Running time on local:
# - itertools.permutations --> 2.41s
# - next_permutation --> 0.95s
# --> next_permutation should AC, itertools.permutations: either AC or TLE.


def next_permutation(case):
    for index in range(1,len(case)):
        Px_index = len(case) - 1 - index
        # Start travelling from the end of the Data Structure
        Px = case[-index-1]
        Px_1 = case[-index]

        # Search for a pair where latter the is greater than prior
        if Px < Px_1 :
            suffix = case[-index:]
            pivot = Px
            minimum_greater_than_pivot_suffix_index = -1
            suffix_index=0

            # Find the index inside the suffix where ::: [minimum value is greater than the pivot]
            for Py in suffix:
                if pivot < Py:
                    if minimum_greater_than_pivot_suffix_index == -1 or   suffix[minimum_greater_than_pivot_suffix_index] >= Py:
                        minimum_greater_than_pivot_suffix_index=suffix_index
                suffix_index +=1
            # index in the main array
            minimum_greater_than_pivot_index = minimum_greater_than_pivot_suffix_index + Px_index +1

            # SWAP
            temp = case[minimum_greater_than_pivot_index]
            case[minimum_greater_than_pivot_index] = case[Px_index]
            case[Px_index] = temp

            # Sort suffix
            new_suffix = case[Px_index+1:]
            new_suffix.sort()

            # Build final Version
            new_prefix = case[:Px_index+1]
            next_permutation = new_prefix + new_suffix
            return next_permutation
        elif index == (len(case) -1):
            # This means that this is at the highest possible lexicographic order
            return False


for test in range(ntest):
    a = raw_input().replace(' ', '')
    cnt = 0  # How many valid date?
    smallest_date = None
    perm = sorted(a)
    while True:
        date_str = ''.join(perm)
        try:
            date = datetime.datetime.strptime(date_str, '%d%m%Y')
            if date.year >= 2000:
                if smallest_date is None or date < smallest_date:
                    smallest_date = date
                cnt += 1
        except ValueError:
            cnt += 0

        # Process next permutation
        perm = next_permutation(perm)
        if not perm:
            # No more permutation
            break

    if cnt > 0:
        print "%d %02d %02d %04d" % (cnt, smallest_date.day, smallest_date.month, smallest_date.year)
    else:
        print cnt
