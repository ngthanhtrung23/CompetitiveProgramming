
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

int n, r[22], m[22];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> m[i];
        FOR(i,1,n) cin >> r[i];

        int cnt = 0;
        int all = 1000111;
        FOR(i,0,all) {
            int good = 0;
            FOR(j,1,n) if (i % m[j] == r[j]) {
                good = 1;
                break;
            }
            cnt += good;
        }
        cout << (cnt / (double) all) << endl;
    }
}
