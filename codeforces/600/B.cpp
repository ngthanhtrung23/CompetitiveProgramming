
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

const int MN = 200111;

int a[MN], b[MN];
int n, m;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,m) scanf("%d", &b[i]);

        a[++n] = 1000111000;
        sort(a+1, a+n+1);
        FOR(i,1,m) {
            int x = upper_bound(a+1, a+n+1, b[i]) - a - 1;
            printf("%d ", x);
        }
        puts("");
    }
}
