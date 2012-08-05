
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

const int MN = 100111;

bool mark[MN], inq[MN];
queue<int> q;
int n, m, k;
vector<int> ke[MN];

void init(int n) {
    memset(mark, false, sizeof mark);
    memset(inq, false, sizeof inq);
    FOR(i,1,n) ke[i].clear();
}

int d[MN], s, t;

bool check(int x) {
    FOR(i,1,n) d[i] = 1000111000;
    d[s] = 0;
    q.push(s);
    memset(inq, false, sizeof inq);

    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = false;
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            int now = d[u] + 1;
            if (now > x) continue;
            if (mark[v]) now = 0;

            if (d[v] > now) {
                d[v] = now;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (d[t] < 1000111000) return true;
    else return false;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        init(n);
        FOR(i,1,k) {
            int u; scanf("%d", &u);
            mark[u] = true;
        }
        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v);
            ke[v].PB(u);
        }
        scanf("%d%d", &s, &t);
        int l = 1, r = n + 1, res = n + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        if (res > n) res = -1;
        printf("%d\n", res);
    }
    return 0;
}
