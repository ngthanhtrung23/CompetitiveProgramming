
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

const int MN = 100111;

int a[MN], n;
char tmp[MN];
pair<int,int> x[MN];

int main() {
    while (scanf("%d\n", &n) == 1) {
        scanf("%s\n", &tmp[0]);
        FOR(i,1,n) a[i] = tmp[i-1] - '0';

        int nx = 0;
        FOR(i,1,n) {
            if (nx == 0 || a[i] != x[nx].first) {
                ++nx;
                x[nx].first = a[i];
                x[nx].second = 1;
            }
            else {
                x[nx].second += 1;
            }
        }

        int res = nx;
        int cnt = 0, cnt2 = 0;
        FOR(i,1,nx) {
            if (x[i].second > 1) ++cnt;
            if (x[i].second > 2) ++cnt2;
        }
        res += max(min(cnt, 2), min(cnt2, 1) * 2);
        cout << res << endl;
    }
}
