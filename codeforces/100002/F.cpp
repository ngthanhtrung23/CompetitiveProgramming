
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string s;
int n;
int f[111][111];
int cycle[111][111][111];

int ndigit(int k) {
    if (k == 0) return 1;
    int res = 0;
    while (k > 0) {
        res++;
        k /= 10;
    }
    return res;
}

int get(int i, int j) {
    if (f[i][j] >= 0) return f[i][j];

    int len = j - i + 1;
    f[i][j] = len;
    FOR(k,i,j-1) {
        f[i][j] = min(f[i][j], get(i, k) + get(k+1, j));
    }

    FOR(l,1,len) if (cycle[i][j][l]) {
        f[i][j] = min(f[i][j], get(i, i+l-1) + 2 + ndigit(len / l));
    }
    return f[i][j];
}

void trace(int i, int j) {
    if (get(i, j) == j - i + 1) {
        FOR(x,i,j) cout << s[x];
        return ;
    }
    FOR(k,i,j-1) if (get(i, j) == get(i, k) + get(k+1, j)) {
        trace(i, k);
        trace(k+1, j);
        return ;
    }
    int len = j - i + 1;
    FOR(l,1,len) if (cycle[i][j][l]) {
        int cur = get(i, i+l-1) + 2 + ndigit(len / l);
        if (cur == f[i][j]) {
            cout << len / l << '(';
            trace(i, i+l-1);
            cout << ')';
            return ;
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("folding.in", "r", stdin);
    freopen("folding.out", "w", stdout);
    while (cin >> s) {
        n = SZ(s);
        s = " " + s + " ";

        memset(cycle, 0, sizeof cycle);
        FOR(i,1,n) FOR(j,1,n) {
            int len = j - i + 1;
            FOR(r,1,len) if (len % r == 0) {
                cycle[i][j][r] = true;
                FOR(u,i+r,j)
                    if (s[u] != s[u-r]) {
                        cycle[i][j][r] = false;
                        break;
                    }
            }
        }

        memset(f, -1, sizeof f);
        int res = get(1, n);
        trace(1, n);
        cout << endl;
    }
}
