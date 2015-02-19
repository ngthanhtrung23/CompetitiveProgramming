
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

const int MN = 100111;
int n, a[MN], res[MN];
pair<int,int> x[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,n) x[i] = make_pair(a[i], i);
        sort(x+1, x+n+1);

        int best = -1;
        FOR(i,1,n) {
            int value = x[i].first, pos = x[i].second;

            if (best < pos) res[pos] = -1;
            else res[pos] = best - pos - 1;

            best = max(best, pos);
        }

        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
    return 0;
}
