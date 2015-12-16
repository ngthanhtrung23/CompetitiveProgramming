
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

int a[55][55];
int nJudge, nProblem;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    while (cin >> nJudge >> nProblem) {
        FOR(i,1,nJudge) {
            int x; cin >> x;
            FOR(j,1,x) cin >> a[i][j];
            while (x < nProblem) a[i][++x] = 50;
        }
        int has = 0;
        int sum = 0;
        FOR(turn,1,nProblem) {
            FOR(i,1,nJudge) {
                int cur = a[i][turn];
                if (cur >= sum) {
                    sum += cur;
                    ++has;

                    if (has == nProblem) break;
                }
            }
            if (has == nProblem) break;
        }
        while (has < nProblem) ++has, sum += 50;
        cout << sum << endl;
    }
}
