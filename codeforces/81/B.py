import re

s = raw_input()
s = s.replace(',', ', ')
s = s.replace('...', ' ...')
s = re.sub(r'\s+', ' ', s)
s = re.sub(r'(?<!,) ,', ',', s)
s = re.sub(r'\.\.\. (?=\d)', '...', s)
s = s.strip()

print s
