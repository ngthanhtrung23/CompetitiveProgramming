
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

string a[7];
bool hasSolution;

struct Board {
    string s[33];
    int m, n;

    void init(int _m, int _n) {
        m = _m; n = _n;
        REP(i,m) {
            s[i] = "";
            REP(j,n) s[i] += '.';
        }
    }

    bool hor(string cur, int i, int j) {
        REP(jj,SZ(cur)) {
            if (s[i][j + jj] == '.') {
                s[i][j + jj] = cur[jj];
            }
            else {
                if (s[i][j + jj] != cur[jj]) return false;
            }
        }
        return true;
    }

    bool ver(string cur, int i, int j) {
        REP(ii,SZ(cur)) {
            if (s[i + ii][j] == '.') {
                s[i + ii][j] = cur[ii];
            }
            else {
                if (s[i + ii][j] != cur[ii]) return false;
            }
        }
        return true;
    }
} cur, res;

bool operator < (const Board& a, const Board& b) {
    REP(i,min(a.m, b.m)) {
        if (a.s[i] < b.s[i]) return true;
        if (a.s[i] > b.s[i]) return false;
    }
    return false;
}

bool check() {
    if (a[4].size() != a[1].size() + a[6].size() - 1) return false;
    if (a[3].size() != a[2].size() + a[5].size() - 1) return false;

    int m = a[3].size();
    int n = a[4].size();
    cur.init(m, n);

    if (!cur.hor(a[1], 0, 0)) return false;
    if (!cur.ver(a[2], 0, 0)) return false;
    if (!cur.ver(a[3], 0, a[1].size() - 1)) return false;
    if (!cur.hor(a[4], a[2].size() - 1, 0)) return false;
    if (!cur.ver(a[5], a[2].size() - 1, n - 1)) return false;
    if (!cur.hor(a[6], m - 1, a[1].size() - 1)) return false;

    if (!hasSolution || cur < res) res = cur;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[1]) {
        FOR(i,2,6) cin >> a[i];
        sort(a+1, a+7);
        hasSolution = false;
        do {
            if (check()) hasSolution = true;
        } while (next_permutation(a+1, a+7));

        if (!hasSolution) cout << "Impossible" << endl;
        else {
            REP(i,res.m) cout << res.s[i] << endl;
        }
    }
}
