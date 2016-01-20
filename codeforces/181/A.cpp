
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

const int MN = 111;
char a[MN][MN];
int m, n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> m >> n) {
        map<int,int> rows, cols;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] == '*') {
                rows[i] += 1;
                cols[j] += 1;
            }
        }
        for(auto p : rows) if (p.second == 1) cout << p.first << ' ';
        for(auto p : cols) if (p.second == 1) cout << p.first << endl;
    }
}
