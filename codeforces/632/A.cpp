
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

string s[44];
ll after[44], before[44];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll n, each;
    while (cin >> n >> each) {
        FOR(i,1,n) cin >> s[i];

        ll res = 0;
        FORD(i,n,1) {
            if (i == n) after[i] = 0;
            else after[i] = before[i+1];

            if (s[i] == "half") before[i] = after[i] * 2;
            else before[i] = after[i] * 2 + 1;

            res += each * (before[i] / 2);
            res += (each / 2) * (before[i] % 2);
        }
        cout << res << endl;
    }
}
