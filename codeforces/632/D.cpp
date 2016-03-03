
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

const int MN = 1000111;
int n, m, a[MN], cnt[MN], has[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        memset(cnt, 0, sizeof cnt);

        FOR(i,1,n) {
            if (a[i] < MN) cnt[a[i]] ++;
        }

        memset(has, 0, sizeof has);
        FOR(val,1,MN-1) {
            for(int x = val; x < MN; x += val)
                has[x] += cnt[val];
        }
        int l = 1;
        FOR(i,2,m) if (has[i] > has[l]) l = i;

        cout << l << ' ' << has[l] << endl;
        FOR(i,1,n) if (l % a[i] == 0) cout << i << ' ';
        cout << endl;
    }
}
