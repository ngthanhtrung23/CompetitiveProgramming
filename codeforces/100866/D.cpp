
#include <bits/stdc++.h>
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int h1, h2, m1, m2, s1, s2;
    char c1, c2;
    scanf("%d:%d:%d%cM", &h1, &m1, &s1, &c1);
    scanf("%d:%d:%d%cM", &h2, &m2, &s2, &c2);

    h1 %= 12;
    h2 %= 12;

    int t1 = h1 * 3600 + m1 * 60 + s1; if (c1 == 'P') t1 += 12 * 3600;
    int t2 = h2 * 3600 + m2 * 60 + s2; if (c2 == 'P') t2 += 12 * 3600;

    int res = t2 - t1;
    if (res < 0) res += 24 * 3600;
    if (res == 0) res = 24 * 3600;

    printf("%02d:%02d:%02d\n", res / 3600, (res % 3600) / 60, res % 60);
}
