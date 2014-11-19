#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 200111;

struct Node {
    int d[2][2];

    void print() {
        REP(i,2) {
            REP(j,2) cout << d[i][j] << ' ';
            cout << endl;
        }
    }
} it[MN * 4], empty;

void update(int &x, int val) {
    if (x < 0) x = val;
    else x = min(x, val);
}

Node operator + (const Node &a, const Node &b) {
    Node res; memset(res.d, -1, sizeof res.d);
    REP(x,2) REP(y,2) REP(z,2) {
        if (a.d[x][y] >= 0 && b.d[y][z] >= 0)
            update(res.d[x][z], a.d[x][y] + b.d[y][z] + 1);
    }
    return res;
}

int n, q;
char a[2][MN];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
#define MID ((l + r) >> 1)

void build(int i, int l, int r) {
    if (l == r) {
        REP(x,2) REP(y,2)
            if (a[x][l] == '.' && a[y][l] == '.')
                it[i].d[x][y] = (x == y) ? 0 : 1;
            else it[i].d[x][y] = -1;
        return ;
    }
    if (l + 1 == r) {
        memset(it[i].d, -1, sizeof it[i].d);
        REP(x,2) {
            if (a[x][l] == '.' && a[x][r] == '.') update(it[i].d[x][x], 1);
            if (a[x][l] == '.' && a[x][r] == '.' && a[1-x][r] == '.') update(it[i].d[x][1-x], 2);
            if (a[x][l] == '.' && a[1-x][l] == '.' && a[1-x][r] == '.') update(it[i].d[x][1-x], 2);
        }
        build(CT(i), l, MID);
        build(CP(i), MID+1, r);
        return ;
    }
    build(CT(i), l, MID);
    build(CP(i), MID+1, r);

    it[i] = it[CT(i)] + it[CP(i)];
    // cout << l << " --> " << r << endl;
    // it[i].print();
}

Node get(int i, int l, int r, int u, int v) {
    if (u <= l && r <= v) {
        // cout << l << ' ' << r << ' ' << u << ' ' << v << endl;
        // it[i].print();
        return it[i];
    }
    if (v <= MID) {
        Node res = get(CT(i), l, MID, u, v);
        // cout << l << ' ' << r << ' ' << u << ' ' << v << endl;
        // res.print();
        return res;
    }
    if (MID+1 <= u) {
        Node res = get(CP(i), MID+1, r, u, v);
        // cout << l << ' ' << r << ' ' << u << ' ' << v << endl;
        // res.print();
        return res;
    }
    Node res = get(CT(i), l, MID, u, v) + get(CP(i), MID+1, r, u, v);
    // cout << l << ' ' << r << ' ' << u << ' ' << v << endl;
    // res.print();
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    empty.d[0][1] = empty.d[1][0] = 1;
    while (cin >> n >> q) {
        REP(t,2) FOR(i,1,n) cin >> a[t][i];
        build(1, 1, n);
        while (q--) {
            int from, to; cin >> from >> to;
            if (from == to) {
                cout << 0 << endl;
                continue;
            }
            if (abs(from - to) == n) {
                cout << 1 << endl;
                continue;
            }
            int r1 = (from - 1) / n, c1 = from % n; if (c1 == 0) c1 = n;
            int r2 = (to - 1) / n, c2 = to % n; if (c2 == 0) c2 = n;
            if (c1 > c2) {
                swap(r1, r2);
                swap(c1, c2);
            }
            Node cur = get(1, 1, n, c1, c2);
            // cur.print();
            cout << cur.d[r1][r2] << "\n";
        }
    }
    return 0;
}
