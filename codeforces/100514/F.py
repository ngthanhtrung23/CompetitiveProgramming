s = input()

# print(s)

hash_value = 0
for c in s:
    hash_value = hash_value * 15 + ord(c) - ord('a')

# print(hash_value)

str = []
while hash_value > 0:
    str.append(hash_value % 27)
    hash_value = hash_value // 27

# print(str)

for i in reversed(str):
    print(chr(i + ord('a') - 1), end="")
