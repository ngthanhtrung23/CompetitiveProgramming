
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
#define double long double
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

double sumlog[1000111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(30);
    int w, h, n;
    while (cin >> w >> h >> n) {
        sumlog[0] = 0.0;
        FOR(i,1,n) sumlog[i] = sumlog[i-1] + log(i);

        double res = 0.0;
        FOR(k,0,n) {
            double l = sumlog[n] - sumlog[k] - sumlog[n-k] - n * log(2);
            double cur = exp(l - 2*log(k+1.0) - 2*log(n-k+1.0) + log(w) + log(h));
            res += cur;
        }
        cout << res << endl;
    }
}
