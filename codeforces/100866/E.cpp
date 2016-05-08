
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

const int MN = 100111;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, k, m;
    while (GI(n) == 1 && GI(k) == 1 && GI(m) == 1) {
        vector<int> a;
        FOR(i,1,n) {
            int sum = 0, nn = 1000111000111000111LL;
            FOR(j,1,m) {
                int x; GI(x);
                nn = min(nn, x);
                sum += x;
            }
            if (nn > 2) a.push_back(sum);
        }
        sort(a.begin(), a.end(), greater<int>());
        if (SZ(a) < k || a[k-1] != a[k]) cout << 0 << endl;
        else cout << a[k-1] << endl;
    }
}
