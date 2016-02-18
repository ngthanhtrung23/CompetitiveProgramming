
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

const int MN = 1011;
char a[MN][MN];
int n;

bool check() {
    FOR(i,1,n) FOR(j,i+1,n)
        if (a[i][j] == '-') {
            bool ok = false;
            FOR(k,1,n) if (a[i][k] + a[j][k] == '1' + '2') {
                ok = true;
                break;
            }
            if (!ok) return false;
        }
    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) scanf("%s\n", &a[i][1]);

        while (true) {
            FOR(i,1,n) FOR(j,1,n)
                if (a[i][j] != '-') a[i][j] = a[j][i] = rand() % 2 + '1';

            if (check()) {
                FOR(i,1,n) {
                    FOR(j,1,n) cout << a[i][j];
                    cout << '\n';
                }
                break;
            }
        }
    }
}
