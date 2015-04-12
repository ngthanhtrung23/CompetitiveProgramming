#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int a[1011];
int f[1011][1011];

void init() {
    FOR(bound,1,1000) {
        FOR(i,1,1000) {
            if (i <= bound) f[bound][i] = 0;
            else {
                f[bound][i] = i;
                FOR(x,1,i-1)
                    f[bound][i] = min(f[bound][i], f[bound][x] + f[bound][i-x] + 1);
            }
        }
    }
}

int main() {
    int ntest; cin >> ntest;
    init();
    FOR(test,1,ntest) {
        int n; cin >> n;
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        int res = 1011;
        REP(before,600) FOR(eat,1,1000) {
            int cur = eat + before;

            FOR(i,1,n)
                cur += f[eat][a[i]];

            res = min(res, cur);
        }
        cout << "Case #" << test << ": " << res << endl;
        if (test % 10 == 0) cerr << test << endl;
    }
    return 0;
}

