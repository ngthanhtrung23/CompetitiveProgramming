
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

const int MN = 1011;
string a[MN];

int dist(const string& a, const string& b) {
    int res = 0;
    REP(i,SZ(a)) if (a[i] != b[i]) ++res;
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        int res = 6;
        FOR(i,1,n) FOR(j,i+1,n) {
            int t = dist(a[i], a[j]);
            if (t % 2 == 0) res = min(res, t / 2 - 1);
            else res = min(res, t / 2);
        }

        cout << res << endl;
    }
}
