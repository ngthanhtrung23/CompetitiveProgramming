n = int(raw_input())
print ('NO', 'YES')[any([n % x == 0 for x in (4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 774, 777)])]
