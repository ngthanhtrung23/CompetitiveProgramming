#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

int n, m, BASE;
vector<int> ke[MN];

long long power(int x, int k) {
    if (k == 0) return 1 % BASE;
    if (k == 1) return x % BASE;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % BASE;
    if (k & 1) return (mid * x) % BASE;
    else return mid;
}

bool mark[MN];
int first, last, qu[MN];

void bfs(int u) {
    first = 1, last = 1; qu[1] = u;
    mark[u] = true;
    while (first <= last) {
        int u = qu[first++];
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (mark[v]) continue;

            mark[v] = true;
            qu[++last] = v;
        }
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &BASE) == 3) {
        FOR(i,1,n) ke[i].clear();
        memset(mark, false, sizeof mark);

        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v); ke[v].PB(u);
        }

        long long res = 1, cnt = 0;
        FOR(i,1,n) if (!mark[i]) {
            bfs(i);
            res = (res * last) % BASE;
            ++cnt;
        }
        if (cnt == 1) {
            printf("%d\n", 1 % BASE);
            continue;
        }
        res = (res * power(n, cnt - 2)) % BASE;

        printf("%d\n", (int) res);
    }
    return 0;
}