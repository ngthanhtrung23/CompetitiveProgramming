#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1011;

int n, m, q;
int a[MN][MN];
set<int> row[MN], col[MN];

void add(int i, int j) {
    row[i].insert(j);
    col[j].insert(i);
}

void remove(int i, int j) {
    row[i].erase(j);
    col[j].erase(i);
}

inline int getRowLeft(int u, int v) {
    __typeof(row[u].begin()) it = row[u].lower_bound(v);
    --it;
    return (*it) + 1;
}

inline int getRowRight(int u, int v) {
    __typeof(row[u].begin()) it = row[u].lower_bound(v);
    return (*it) - 1;
}

inline int getColLeft(int u, int v) {
    __typeof(col[v].begin()) it = col[v].lower_bound(u);
    --it;
    return (*it) + 1;
}

inline int getColRight(int u, int v) {
    __typeof(col[v].begin()) it = col[v].lower_bound(u);
    return (*it) - 1;
}

int solve(int u, int v) {
    if (a[u][v] == 0) return 0;

    int res = 0, left, right;
    // Go up
    left = 1; right = n;
    FORD(i,u,1) {
        if (a[i][v] == 0) break;
        left = max(left, getRowLeft(i, v));
        right = min(right, getRowRight(i, v));

        res = max(res, (right - left + 1) * (u - i + 1));
    }

    // Go down
    left = 1; right = n;
    FOR(i,u,m) {
        if (a[i][v] == 0) break;
        left = max(left, getRowLeft(i, v));
        right = min(right, getRowRight(i, v));

        res = max(res, (right - left + 1) * (i - u + 1));
    }

    // Go left
    left = 1; right = m;
    FORD(j,v,1) {
        if (a[u][j] == 0) break;
        left = max(left, getColLeft(u, j));
        right = min(right, getColRight(u, j));

        res = max(res, (right - left + 1) * (v - j + 1));
    }

    // Go right
    left = 1; right = m;
    FOR(j,v,n) {
        if (a[u][j] == 0) break;
        left = max(left, getColLeft(u, j));
        right = min(right, getColRight(u, j));

        res = max(res, (right - left + 1) * (j - v + 1));
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> q) {
        FOR(i,1,m) {
            row[i].clear();
            row[i].insert(0);
            row[i].insert(n+1);
        }
        FOR(j,1,n) {
            col[j].clear();
            col[j].insert(0);
            col[j].insert(m+1);
        }

        FOR(i,1,m) {
            FOR(j,1,n) {
                cin >> a[i][j];
                if (a[i][j] == 0) {
                    add(i, j);
                }
            }
        }

        while (q--) {
            int typ, u, v; cin >> typ >> u >> v;
            if (typ == 1) {
                if (a[u][v] == 0) remove(u, v);
                a[u][v] = 1 - a[u][v];
                if (a[u][v] == 0) add(u, v);
            }
            else {
                cout << solve(u, v) << "\n";
            }
        }
    }
    return 0;
}
