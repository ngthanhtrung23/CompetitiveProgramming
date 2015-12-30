
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    string x, y;
    while (cin >> n >> x >> y) {
        if (y == "week") {
            if (n == 5 || n == 6) cout << 53 << endl;
            else cout << 52 << endl;
        }
        else {
            if (n <= 29) cout << 12 << endl;
            else if (n == 30) cout << 11 << endl;
            else cout << 7 << endl;
        }
    }
}
