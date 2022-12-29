"""
Compiles BF code -> C++

Has several improvements which helps with debugging:

1. assert if a loop [...] doesn't use same pointer at beginning and end
2. "batch" + and - together, so that C++ code is more readable
3. In compiled C++ code, use a[index] instead of *ptr so it's more readable
4. "P" command in BF prints current state of cells
"""

# Read entire BF program (can contain invalid characters)
program = ""
import sys
for line in sys.stdin:
    program += line


# Remove invalid characters
def only_valid_bf_chars(program):
    res = ""
    for c in program:
        if c in '><+-,.[]P':
            res += c
    return res


program = only_valid_bf_chars(program)


def compress(program):
    """
    Compress program: For consecutive < > + -, we try to combine them
    Returns: list[[command, cnt]]
    """
    res = []
    for c in program:
        if len(res) == 0 or res[-1][0] != c or c in ',.[]':
            res.append([c, 1])
        else:
            res[-1][1] += 1
    return res

# print(compress(program))


print("#include <bits/stdc++.h>")
print("#include \"debug.h\"")
print("using namespace std;")
print("int a[30000] = {0};")
print("int main() {")

depth = 1
ptr = 0
start_loop_ptr = []
for command, cnt in compress(program):
    if command == '>':
        ptr += cnt
    elif command == '<':
        ptr -= cnt
    elif command == '+':
        print(f"{' ' * 4 * depth}a[{ptr}] += {cnt};")
    elif command == '-':
        print(f"{' ' * 4 * depth}a[{ptr}] -= {cnt};")
    elif command == '.':
        print(f"{' ' * 4 * depth}putchar(a[{ptr}]);")
    elif command == ',':
        print(f"{' ' * 4 * depth}a[{ptr}] = getchar();")
    elif command == '[':
        print(f"{' ' * 4 * depth}while (a[{ptr}])", '{')
        depth += 1
        start_loop_ptr.append(ptr)
    elif command == ']':
        depth -= 1
        print(f"{' ' * (4 * depth - 1)}", '}')
        assert(len(start_loop_ptr) > 0)
        assert(start_loop_ptr[-1] == ptr)
        start_loop_ptr = start_loop_ptr[:-1]
    elif command == 'P':
        print(f"{' ' * 4 * depth}PR0(a, 11);")
    else:
        print("ERROR: UNKNOWN COMMAND ", command)

print("}") # end of main
