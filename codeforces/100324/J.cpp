
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

set< vector<int> > all[22];
int n;

int id[22];

bool intersect(int start, int i, vector<int> x) {
    for(int j = start; j+1 < i; j += 2) {
        int l = id[i-1], r = id[i]; if (l > r) swap(l, r);
        int u = id[j+1], v = id[j]; if (u > v) swap(u, v);

        if (r < u || v < l) continue;
        if (u <= l && r <= v) continue;
        if (l <= u && v <= r) continue;

        return true;
    }
    return false;
}

bool cutN(int start, int i, vector<int>& x) {
    for(int j = start; j + 1 < i; j += 2) {
        if (id[j] < id[n] && id[n] < id[j+1]) return true;
        if (id[j] > id[n] && id[n] > id[j+1]) return true;
    }
    return false;
}

bool check(int i, int n, vector<int> x) {
    REP(i,SZ(x)) id[x[i]] = i;

    if (i % 2 == 1) {
        if (id[i-1] < id[1] && id[1] < id[i]) return false;
        if (id[i-1] > id[1] && id[1] > id[i]) return false;

        if (intersect(2, i, x)) return false;

        if (i == n) {
            if (cutN(1, i, x)) return false;
        }
    }
    else {
        if (intersect(1, i, x)) return false;
        if (i == n) {
            if (cutN(2, i, x)) return false;
        }
    }

    return true;
}

void get(int i, int n, vector<int> x) {
    if (i > n) return ;

    FOR(pos,0,SZ(x)) {
        vector<int> y = x;
        y.insert(y.begin() + pos, i);
        if (!check(i, n, y)) continue;

        if (!all[i].count(y)) {
            all[i].insert(y);
            get(i+1, n, y);
        }
    }
}

int res[16] = {
    2,
    4,
    4,
    12,
    16,
    56,
    84,
    324,
    524,
    2152,
    3656,
    15704,
    27640,
    122776,
    221908,
    1011756,
};

int main() {
    ios :: sync_with_stdio(false);
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);

    while (cin >> n) {
        cout << res[n-1] << endl;
        continue;
        FOR(i,1,n) all[i].clear();

        vector<int> x;
        get(1, n, x);
        cout << 2 * SZ(all[n]) << endl;
    }
}

