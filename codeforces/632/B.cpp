
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

const int MN = 500111;
string s;
int n;
ll x[MN], suma[MN], sumb[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> x[i];
        cin >> s; s = " " + s + " ";

        FOR(i,1,n) {
            suma[i] = suma[i-1];
            sumb[i] = sumb[i-1];

            if (s[i] == 'A') suma[i] += x[i];
            else sumb[i] += x[i];
        }
        ll res = max(sumb[n], suma[n]);

        FOR(i,1,n) {
            // flip pieces 1 --> i
            res = max(res, suma[i] + sumb[n] - sumb[i]);
            
            // flip pieces i --> n
            res = max(res, sumb[i-1] + suma[n] - suma[i-1]);
        }
        cout << res << endl;
    }
}
