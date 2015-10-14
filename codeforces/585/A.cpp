
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 4011;

int v[MN], d[MN], p[MN], n, leave[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> v[i] >> d[i] >> p[i];
        memset(leave, 0, sizeof leave);

        FOR(i,1,n) if (!leave[i]) {
//            DEBUG(i);
//            PR(p, n);
            // reduce the confidence in the queue
            int red = v[i], j = i + 1;
            while (red > 0 && j <= n) {
                if (leave[j]) ++j;
                else {
                    p[j] -= red;
                    if (p[j] < 0) p[j] = -1;
                    red--;
                    ++j;
                }
            }
//            PR(p, n);
            // more child cry & leave
            while (true) {
                bool good = false;
                FOR(j,i+1,n) if (p[j] < 0 && !leave[j]) {
                    good = true;
                    leave[j] = true;
                    FOR(k,j+1,n) if (!leave[k]) {
                        p[k] -= d[j];
                        if (p[k] < 0) p[k] = -1;
                    }
                }
                if (!good) break;
            }
//            PR(p, n);
        }
        int cnt = 0;
        FOR(i,1,n) if (!leave[i]) ++cnt;
        cout << cnt << endl;
        FOR(i,1,n) if (!leave[i]) cout << i << ' '; cout << endl;
    }
}
