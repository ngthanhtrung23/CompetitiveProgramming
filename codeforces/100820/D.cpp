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

int a[3], b[3];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> a[0] >> a[1] >> a[2]) {
        cin >> b[0] >> b[1] >> b[2];
        sort(a, a+3);
        sort(b, b+3);

        if (a[2] == b[2]
                && a[2]*a[2] == a[0]*a[0] + a[1]*a[1]
                && a[1] == b[1]
                && a[0] == b[0])
            cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}
