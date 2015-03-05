
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
using namespace std;

string a[22];
map<string,int> id;
int bad[22][22];

int main() {
    int n, k;
    while (cin >> n >> k) {
        memset(bad, 0, sizeof bad);
        id.clear();
        REP(i,n) cin >> a[i];
        sort(a, a+n);
        REP(i,n) id[a[i]] = i;
        REP(i,k) {
            string x, y; cin >> x >> y;
            bad[id[x]][id[y]] = 1;
        }
        int best = 0, save = 0;
        REP(mask,TWO(n)) if (__builtin_popcount(mask) > best) {
            int sum = 0;
            REP(i,n) if (CONTAIN(mask,i))
                REP(j,n) if (CONTAIN(mask,j))
                    sum += bad[i][j];

            if (sum == 0) {
                best = __builtin_popcount(mask);
                save = mask;
            }
        }
        cout << best << endl;
        REP(i,n) if (CONTAIN(save, i)) cout << a[i] << endl;
    }
    return 0;
}

