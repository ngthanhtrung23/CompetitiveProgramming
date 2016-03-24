
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

const int MN = 200111;
string a[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        set<string> s;
        FORD(i,n,1) {
            if (!s.count(a[i])) {
                s.insert(a[i]);
                cout << a[i] << '\n';
            }
        }
    }
}
