
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100111;
int n, m, color[MN];
vector<int> ke[MN];

int cnt0, cnt1;
bool hasOddCycle(int u) {
    if (color[u] == 0) ++cnt0;
    else ++cnt1;

    for(int v : ke[u]) {
        if (color[v] < 0) {
            color[v] = 1 - color[u];
            if (hasOddCycle(v)) {
                return true;
            }
        }
        else {
            if (color[v] == color[u]) return true;
        }
    }
    return false;
}

ll add1;
bool check0() {
    cnt0 = cnt1 = 0;
    add1 = 0;

    memset(color, -1, sizeof color);
    FOR(i,1,n) if (color[i] < 0) {
        int cur0 = cnt0, cur1 = cnt1;
        color[i] = 0;
        if (hasOddCycle(i)) {
            cout << "0 1" << endl;
            return true;
        }

        cur0 = cnt0 - cur0;
        cur1 = cnt1 - cur1;

        add1 += cur0 * (cur0-1LL) / 2;
        add1 += cur1 * (cur1-1LL) / 2;
    }

    return false;
}

bool check1() {
    if (add1) {
        cout << 1 << ' ' << add1 << endl;
        return true;
    }
    return false;
}

bool check2() {
    if (m == 0) return false;
    cout << 2 << ' ' << m * (n-2LL) << endl;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        if (check0()) continue;
        if (check1()) continue;
        if (check2()) continue;
        cout << 3 << ' ' << n*(n-1LL)*(n-2LL) / 6 << endl;
    }
}

