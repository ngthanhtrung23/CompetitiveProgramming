
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

int n;
char a[200111], b[200111];
int id[300][300];

int main() {
    while (scanf("%d\n", &n) == 1) {
        gets(a); gets(b);
        memset(id, 0, sizeof id);
        REP(i,n) id[a[i]][b[i]] = i + 1;

        int best = 0, savei = -1, savej = -1;
        REP(i,n) if (a[i] != b[i]) ++best;

        int initial = best;

        FOR(x,'a','z') FOR(y,'a','z')
            if (id[x][y])
                FOR(u,'a','z') FOR(v,'a','z')
                    if (id[u][v] && id[u][v] != id[x][y]) {
                        int cur = initial;
                        if (x != y) --cur;
                        if (u != v) --cur;

                        if (x != v) ++cur;
                        if (y != u) ++cur;

                        if (cur < best) {
                            best = cur;
                            savei = id[x][y];
                            savej = id[u][v];
                        }
                    }
        cout << best << endl;
        cout << savei << ' ' << savej << endl;
    }
    return 0;
}
