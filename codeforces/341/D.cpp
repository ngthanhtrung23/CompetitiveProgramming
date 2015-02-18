#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 1;

int n;
LL a[N][N], b[N][N], c[N][N], d[N][N];

void insert(int x, int y, LL v) {
    if (x >= 1 && y >= 1) {
        if (x * y % 2 == 1) {
            for (int i = x; i <= n; i += -i & i) {
                for (int j = y; j <= n; j += -j & j) {
                    a[i][j] ^= v;
                }
            }
        }

        if (y % 2 == 1) {
            for (int i = x; i >= 1; i -= -i & i) {
                for (int j = y; j <= n; j += -j & j) {
                    b[i][j] ^= v;
                }
            }
        }

        if (x % 2 == 1) {
            for (int i = x; i <= n; i += -i & i) {
                for (int j = y; j >= 1; j -= -j & j) {
                    c[i][j] ^= v;
                }
            }
        }

        for (int i = x; i >= 1; i -= -i & i) {
            for (int j = y; j >= 1; j -= -j & j) {
                d[i][j] ^= v;
            }
        }
    }
}

LL query(int x, int y) {
    if (x <= 0 || y <= 0) {
        return 0;
    }
    LL ret = 0;
    for (int i = x; i >= 1; i -= -i & i) {
        for (int j = y; j >= 1; j -= -j & j) {
            ret ^= a[i][j];
        }
    }

    if (x % 2 == 1) {
        for (int i = x + 1; i <= n; i += -i & i) {
            for (int j = y; j >= 1; j -= -j & j) {
                ret ^= b[i][j];
            }
        }
    }

    if (y % 2 == 1) {
        for (int i = x; i >= 1; i -= -i & i) {
            for (int j = y + 1; j <= n; j += -j & j) {
                ret ^= c[i][j];
            }
        }
    }

    if (x * y % 2 == 1) {
        for (int i = x + 1; i <= n; i += -i & i) {
            for (int j = y + 1; j <= n; j += -j & j) {
                ret ^= d[i][j];
            }
        }
    }
    return ret;
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int t, x1, y1, x2, y2;
        long long v;
        scanf("%d%d%d%d%d", &t, &x1, &y1, &x2, &y2);
        x1 --, y1 --;
        if (t == 1) {
            long long ret = 0;
            ret ^= query(x2, y2);
            ret ^= query(x1, y1);
            ret ^= query(x2, y1);
            ret ^= query(x1, y2);
            printf("%I64d\n", ret);
        } else {
            scanf("%I64d", &v);
            insert(x2, y2, v);
            insert(x1, y1, v);
            insert(x2, y1, v);
            insert(x1, y2, v);
        }
    }
    return 0;
}
