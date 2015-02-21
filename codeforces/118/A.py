vowels = 'aeiouy'
s = raw_input()
s = '.'.join([x for x in s.lower() if x not in vowels])
print '.' + s
