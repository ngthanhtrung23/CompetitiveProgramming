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

int c[100111];

int dist(char a, char b) {
    if (a > b) swap(a, b);
    return min(b - a, a - 'a' + 1 + 'z' - b);
}

string s;
int n, pos;
int dist2(int u, int v) {
    if (u > v) swap(u, v);
    return min(v - u, n-v + 1 + u-1);
}

int solve() {
    int first = -1, last = -1;
    int mid = n / 2;

    int sum = 0;
    FOR(i,1,mid) if (c[i]) {
        if (first < 0) first = i;
        last = i;

        sum += c[i];
    }

    if (first < 0) return sum;

    int res = 1e9;

    res = min(res, dist2(pos, first) + dist2(first, last));
    res = min(res, dist2(pos, last) + dist2(last, first));
    return res + sum;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(a,'a','z') FOR(b,'a','z')
        if (a != b) assert(dist(a, b) > 0);
    while (ntest--) {
        cin >> n >> pos;
        cin >> s;
        s = " " + s + " ";
        if (pos > n - pos + 1) pos = n - pos + 1;

        int mid = n / 2;
        FOR(i,1,mid) {
            c[i] = c[n+1-i] = dist(s[i], s[n+1-i]);
        }

        cout << solve() << endl;
    }
}
