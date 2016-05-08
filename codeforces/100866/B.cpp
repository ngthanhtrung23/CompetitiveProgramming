
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

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    int C, N, dc, dt;
    while (cin >> C >> N >> dc >> dt) {
        int k = ((dc * (100 - dt)) / dt - C) / dc - 10;
        if (k < 0) k = 0;

        while ((C + k*dc) * dt < dc * (100 - dt)) ++k;

        assert((C + k*dc) * dt >= dc * (100 - dt));
        assert((C + (k-1)*dc) * dt < dc * (100 - dt));

        if (k > N) k = N;
        cout << k << ' ' << N-k << endl;
    }
}
