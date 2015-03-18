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

int nHill, nFrog, nMos, frogs[111], a[111], mos[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nHill >> nFrog >> nMos) {
        FOR(i,1,nFrog) cin >> frogs[i];
        FOR(i,1,nMos) cin >> mos[i];

        FOR(i,1,nFrog) {
            a[i] = 0;
            FOR(j,1,nMos) if (mos[j] % frogs[i] == 0) ++a[i];
        }
        int best = *min_element(a+1, a+nFrog+1);
        int cnt = 0;
        FOR(i,1,nFrog) if (a[i] == best) ++cnt;

        cout << cnt << endl;
        FOR(i,1,nFrog) if (a[i] == best) cout << i << ' ';
        cout << endl;
    }
    return 0;
}
