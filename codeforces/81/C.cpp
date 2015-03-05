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
pair<int,int> a[MN];
int res[MN];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        int x, y; scanf("%d%d", &x, &y);
        FOR(i,1,n) {
            scanf("%d", &a[i].first);
            if (x > y) a[i].second = i;
            else a[i].second = -i;
        }
        sort(a+1, a+n+1);

        if (x == y) {
            FOR(i,1,x) printf("1 ");
            FOR(i,x+1,n) printf("2 ");
            puts("");
            continue;
        }
        else if (x >= y) {
            FOR(i,1,x) res[abs(a[i].second)] = 1;
            FOR(i,x+1,n) res[abs(a[i].second)] = 2;
        }
        else {
            FOR(i,1,y) res[abs(a[i].second)] = 2;
            FOR(i,y+1,n) res[abs(a[i].second)] = 1;
        }
        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
    return 0;
}

