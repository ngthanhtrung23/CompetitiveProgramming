
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

int f[311][311];

int get(int sum, int start) {
    if (sum < 0) return 0;
    if (start > sum) return 0;
    if (start == sum) return 1;
    if (start + start == sum) return 2;

    if (f[sum][start] >= 0) return f[sum][start];

    return f[sum][start] = get(sum, start+1) + get(sum - start - start, start);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    memset(f, -1, sizeof f);
    int n;
    while (cin >> n && n) {
        cout << get(n, 1) << '\n';
    }
}
