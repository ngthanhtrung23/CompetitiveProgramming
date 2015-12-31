
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

int n;
char a[1<<9][1<<9];

void solve(int n) {
    if (n == 0) {
        a[0][0] = '+';
        return ;
    }

    solve(n-1);
    int mid = 1<<(n-1);

    FOR(i,mid,(1<<n)-1)
        REP(j,mid)
            a[i][j] = a[i-mid][j];

    REP(i,mid)
        FOR(j,mid,(1<<n)-1)
            a[i][j] = a[i][j-mid];

    FOR(i,mid,(1<<n)-1)
        FOR(j,mid,(1<<n)-1)
            a[i][j] = '+' + '*' - a[i-mid][j-mid];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        solve(n);
        REP(i,1<<n) {
            REP(j,1<<n) putchar(a[i][j]);
            puts("");
        }
    }
}
