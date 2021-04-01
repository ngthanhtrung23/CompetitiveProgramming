# first few functions are easy to guess
# for the rest, check what's available in Python math library

# fallocest = cos
# sploop = sin

# tudefy = log10
# fabrate = sqrt

# strustate = math.gamma
# ensalex = math.atan

# chaness = abs
# holofy = math.exp
# quendle

import math
s = raw_input()

s = s.replace('fallocest', 'math.cos')
s = s.replace('sploop', 'math.sin')
s = s.replace('tudefy', 'math.log10')
s = s.replace('fabrate', 'math.sqrt')
s = s.replace('strustate', 'math.gamma')
s = s.replace('ensalex', 'math.atan')
s = s.replace('chaness', 'abs')
s = s.replace('holofy', 'math.exp')
s = s.replace('quendle', 'math.erf')

print eval(s)
