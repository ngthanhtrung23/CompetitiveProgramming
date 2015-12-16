
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

const int MN = 22;
int n;
char a[4][MN][MN], res[MN][MN];
string s;

void solve() {
    FOR(i,1,n) FOR(j,1,n) {
        int cnt = 0;
        REP(turn,4)
            if (a[turn][i][j] == '.') ++cnt;

        if (cnt != 1) {
            cout << "invalid grille" << endl;
            return ;
        }
    }
    int pos = 0;
    REP(turn,4) {
        FOR(i,1,n) {
            FOR(j,1,n) if (a[turn][i][j] == '.') {
                res[i][j] = s[pos++];
            }
        }
    }
    FOR(i,1,n) FOR(j,1,n) cout << res[i][j]; cout << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[0][i][j];
        cin >> s;
//        FOR(i,1,n) {
//            FOR(j,1,n) cout << a[0][i][j];
//            cout << endl;
//        }
        FOR(turn,1,3) {
            FOR(i,1,n) FOR(j,1,n)
                a[turn][i][j] = a[turn-1][n+1-j][i];

//            cout << endl;
//            FOR(i,1,n) {
//                FOR(j,1,n) cout << a[turn][i][j];
//                cout << endl;
//            }
        }
        solve();
    }
}
