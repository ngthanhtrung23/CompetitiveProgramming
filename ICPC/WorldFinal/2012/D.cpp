#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}
string f[111];

#define next next____
int next[1000111];
int count(string p, string s) {
    int lp = SZ(p), ls = SZ(s);

    next[0] = -1; int j = -1;
    FOR(i,1,lp-1) {
        while (j >= 0 && p[i] != p[j+1]) j = next[j];
        if (p[i] == p[j+1]) ++j;
        next[i] = j;
    }

    int res = 0;
    j = -1;
    FOR(i,0,ls-1) {
        while (j >= 0 && s[i] != p[j+1]) j = next[j];
        if (s[i] == p[j+1]) ++j;

        if (j == lp-1) {
            ++res;
            j = next[j];
        }
    }
    return res;
}

int g[111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    f[0] = "0";
    f[1] = "1";
    int n = 1;
    while (true) {
        ++n;
        f[n] = f[n-1] + f[n-2];
        if (SZ(f[n]) >= 100000) {
            break;
        }
    }
    f[26] = f[25] + f[24];
    f[27] = f[26] + f[25];
    f[28] = f[27] + f[26];

    int k; string p;
    int test = 0;
    while (cin >> k >> p) {
        cout << "Case " << ++test << ": ";
        if (k <= 28) cout << count(p, f[k]);
        else {
            g[25] = count(p, f[25]);
            g[26] = count(p, f[26]);
            g[27] = count(p, f[27]);
            g[28] = count(p, f[28]);
            int toEven = g[28] - g[27] - g[26];
            int toOdd = g[27] - g[26] - g[25];
            FOR(i,29,100) {
                g[i] = g[i-1] + g[i-2];
                if (i % 2 == 0) g[i] += toEven;
                else g[i] += toOdd;
            }
            cout << g[k] << endl;
        }
        cout << '\n';
    }
}
