
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A,n)  { cerr << #A << " = "; FOR(_,1,n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A,n) { cerr << #A << " = "; REP(_,n) cerr << A[_] << ' '; cerr << endl; }

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

map<int,int> f;
int A, B, X;

int myround(double x) {
    return (int) (x + 0.5);
}

int get(int x) {
    if (x <= 0) return 0;
    if (x <= max(A, B)) return 1;
    if (f.find(x) != f.end()) return f[x];

    int res = get(x - A) + get(x - B);
    if (SZ(f) < 100111) f[x] = res;

    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);

    double a, b, x;
    while (cin >> a >> b >> x) {
        f.clear();
        A = myround(a * 100000);
        B = myround(b * 100000);
        X = myround(x * 100000);

        cout << get(X) << endl;
    }
}
