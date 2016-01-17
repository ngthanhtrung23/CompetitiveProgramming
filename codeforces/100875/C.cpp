
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

#define int long long
#define double long double
const int MN = 100111;
int N, A, B;
int s[MN], x[MN];

double solve(int B) {
    double res = 0;
    if (B > s[N]) {
        int times = B / s[N];
        B %= s[N];

        FOR(i,1,N) res += x[i] * x[i] / 2.0;

        res *= times;
    }
    FOR(i,1,N) {
        int can = min(B, x[i]);
        res += can * can / 2.0;
        B -= can;
        if (B == 0) break;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> N >> A >> B;
        FOR(i,1,N) {
            cin >> x[i];
            s[i] = x[i] + s[i-1];
        }
        double res = solve(B);
        res -= solve(A);
        cout << "Case #" << test << ": " << (fixed) << setprecision(20) << res / (double) (B - A) << endl;
        cerr << test << endl;
    }
}
