
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

const int MN = 55;
int n, c, p[55], t[55];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> c) {
        FOR(i,1,n) cin >> p[i];
        FOR(i,1,n) cin >> t[i];

        int sumt = 0;
        int limak = 0, rade = 0;
        FOR(i,1,n) {
            sumt += t[i];
            limak += max(0LL, p[i] - sumt * c);
        }
        sumt = 0;
        FORD(i,n,1) {
            sumt += t[i];
            rade += max(0LL, p[i] - sumt * c);
        }
        if (limak == rade) cout << "Tie";
        else if (limak > rade) cout << "Limak";
        else cout << "Radewoosh";
        cout << endl;
    }
}
