
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

int a[200111], n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        vector<int> x[2];
        REP(turn,2) {
            x[turn].clear();
            FOR(i,1,n) cin >> a[i];
            FOR(i,1,n) if (a[i] == 1) {
                FOR(j,i,n) if (a[j]) x[turn].push_back(a[j]);
                FOR(j,1,i-1) if (a[j]) x[turn].push_back(a[j]);
            }
        }
        cout << (x[0] == x[1] ? "YES" : "NO") << endl;
    }
}
