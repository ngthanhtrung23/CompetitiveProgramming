
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 55;
int x[55], y[55];
string part[55];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
            x[i] /= 2;
            y[i] /= 2;

            int r; cin >> r;
        }
        REP(turn,2) {
            FOR(i,1,n) {
                stringstream ss;
                int cur = (turn == 0) ? x[i] : y[i];
                ss << '(' << cur << '*'
                    << "((1-abs((t-" << i << ")))+abs((abs((t-" << i << "))-1)))"
                    << ')';
                part[i] = ss.str();
            }
            string res = "";
            FOR(i,1,n) {
                if (i == 1) res = part[i];
                else res = '(' + res + '+' + part[i] + ')';
            }
            cout << res << endl;
        }
    }
}
