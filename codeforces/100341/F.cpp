
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

const int MN = 100111;
string s;
int f[4][MN];

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}
int max4(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}

int eat(int i) {
    if (s[i] == 'g') {
        f[0][i] = 0;
        f[1][i] = 1;
        f[2][i] = 1;
        f[3][i] = -MN;
        return i + 1;
    }
    int l = i + 1;
    int r = eat(l);
    int j = eat(r);

    REP(t,4) f[t][i] = -MN;

    if (s[i] == 'S') {
        REP(left,2) REP(right,2) REP(mid,2) {
            int ti = left * 2 + right * 1;
            int tl = left * 2 + mid * 1;
            int tr = mid * 2 + right * 1;

            f[ti][i] = max(f[ti][i], f[tl][l] + f[tr][r] - mid);
        }
    }
    if (s[i] == 'P') {
        REP(left,2) REP(right,2) {
            int mask = left * 2 + right;
            f[mask][i] = max(f[mask][i], f[mask][l] + f[mask][r] - left - right);
        }
    }

    return j;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("independent.in", "r", stdin);
    freopen("independent.out", "w", stdout);
    while (cin >> s) {
        int to = eat(0);
        assert(to == SZ(s));

        cout << max4(f[0][0], f[1][0], f[2][0], f[3][0]) << endl;
    }
}
