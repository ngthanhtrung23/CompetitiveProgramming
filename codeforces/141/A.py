r = raw_input
a, b, c = r(), r(), r()
print ('NO', 'YES')[sorted(a+b) == sorted(c)]
