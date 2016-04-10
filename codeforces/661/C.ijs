require 'strings'

print =: 1!:2&2
read =: 1!:1[3

s =: read-.CR

t =: ' ' joinstring LF splitstring s

print +/ ". t