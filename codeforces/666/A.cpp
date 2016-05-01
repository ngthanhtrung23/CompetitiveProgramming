
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
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

int f2[10111], f3[10111], len;
string s;

bool equal(char a, char b, char u, char v) {
    return a == u && b == v;
}
bool equal(char a, char b, char c, char u, char v, char w) {
    return a == u && b == v && c == w;
}

int can2(int i) {
    if (i+2 == len) return 1;
    if (f3[i+2]) return 1;

    if (!f2[i+2]) return 0;
    if (i+3 >= len) return 1;

    if (equal(s[i], s[i+1], s[i+2], s[i+3])) return 0;
    return 1;
}
int can3(int i) {
    if (i+3 == len) return 1;
    if (f2[i+3]) return 1;

    if (!f3[i+3]) return 0;
    if (i+5 >= len) return 1;

    if (equal(s[i], s[i+1], s[i+2], s[i+3], s[i+4], s[i+5])) return 0;
    return 1;
}

bool good[333][333], good3[333][333][333];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        len = SZ(s);
        memset(f2, 0, sizeof f2);
        memset(f3, 0, sizeof f3);
        memset(good, 0, sizeof good);
        memset(good3, 0, sizeof good3);
        f2[len] = f3[len] = 1;
        FORD(i,len-1,5) {
            if (i + 1 < len && can2(i)) {
                f2[i] = 1;
                good[s[i]][s[i+1]] = 1;
            }
            if (i + 2 < len && can3(i)) {
                f3[i] = 1;
                good3[s[i]][s[i+1]][s[i+2]] = 1;
            }
        }
        int cnt = 0;
        FOR(u,'a','z') FOR(v,'a','z') {
            if (good[u][v]) ++cnt;
            FOR(w,'a','z') if (good3[u][v][w]) ++cnt;
        }
        cout << cnt << endl;
        FOR(u,'a','z') FOR(v,'a','z') {
            if (good[u][v]) cout << (char)u << (char)v << '\n';
            FOR(w,'a','z') if (good3[u][v][w]) cout << (char)u << (char)v << (char)w << '\n';
        }
    }
}
