sym = "AHIMOTUVWXYovwx"
mir = {
    'p': 'q',
    'q': 'p',
    'd': 'b',
    'b': 'd',
}

def good(a, b):
    if a in sym and a == b:
        return True
    if a in mir and mir[a] == b:
        return True
    return False


def check(s: str) -> bool:
    for i in range(len(s)):
        j = len(s) - i - 1
        if i == j:
            if not s[i] in sym:
                return False
        if i != j:
            if not good(s[i], s[j]):
                return False
    return True


s = input()
print('TAK' if check(s) else 'NIE')
