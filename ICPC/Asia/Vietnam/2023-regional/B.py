def is_beautiful_scoreboard(N, M, scoreboard):
    # Check if each problem is solved by at least one team
    if not all(any(row[j] == 1 for row in scoreboard) for j in range(M)):
        return "NO"

    # Check if no team solved all problems
    if sum(scoreboard[0]) == M:
        return "NO"

    # Check if each team solved at least one problem
    if sum(scoreboard[-1]) == 0:
        return "NO"

    return "YES"

ntest = int(input())
for test in range(ntest):
    n, m = map(int, input().split())
    scoreboard = []
    for i in range(n):
        scoreboard.append(list(map(int, input().split())))

    print(is_beautiful_scoreboard(n, m, scoreboard))
