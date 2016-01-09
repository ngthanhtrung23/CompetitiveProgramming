
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

ll p[1000111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> p[1] >> p[2]) {
        if (p[1] == 0 && p[1] == p[2]) {
            cout << 0 << ' ' << 0 << endl;
            continue;
        }
        FOR(i,3,1000000) {
            p[i] = p[i-2] - p[i-1];
            if (p[i] < 0) {
                cout << i << ' ' << p[i] << endl;
                break;
            }
        }
    }
}
