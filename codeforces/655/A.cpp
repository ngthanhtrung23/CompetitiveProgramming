
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
#define SZ(x) ((int) (x).size())
using namespace std;

string a[2], b[2];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> a[0] >> a[1] >> b[0] >> b[1]) {
        bool ok = false;
        REP(turn,100) {
            if (a[0][0] == 'X') {
                swap(a[0][0], a[0][1]);
            }
            else if (a[0][1] == 'X') {
                swap(a[0][1], a[1][1]);
            }
            else if (a[1][1] == 'X') {
                swap(a[1][1], a[1][0]);
            }
            else {
                swap(a[1][0], a[0][0]);
            }
            if (a[0] == b[0] && a[1] == b[1]) {
                cout << "YES" << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "NO" << endl;
    }
}
